//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//===========================================================================//
#include <cstdio>
#include <cstring>
#if defined( PLATFORM_WINDOWS )
	#include <libloaderapi.h>
	#include <errhandlingapi.h>
	#include <windef.h>
	#include <winbase.h>
	#include <direct.h> // getcwd
#elif defined( PLATFORM_POSIX )
	#include <dlfcn.h>
	#include <unistd.h>
	#include <type_traits>
	#include <cerrno>
	#define _getcwd getcwd
#endif

#if !defined( DONT_PROTECT_FILEIO_FUNCTIONS )
	#define DONT_PROTECT_FILEIO_FUNCTIONS  // for protected_things.h
#endif

#if defined( PROTECTED_THINGS_ENABLE )
	#undef PROTECTED_THINGS_ENABLE  // from protected_things.h
#endif

#include "interface.h"
#include "basetypes.h"
#include "tier0/dbg.h"
#include "tier0/threadtools.h"
#include "tier1/strtools.h"
#include "tier0/icommandline.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


// ------------------------------------------------------------------------------------ //
// InterfaceReg.
// ------------------------------------------------------------------------------------ //
InterfaceReg::InterfaceReg( const InstantiateInterfaceFn fn, const char* pName )
	: m_CreateFn{ fn }, m_Name{ pName } {
	m_Next = s_InterfaceRegs;
	s_InterfaceRegs = this;
}

// ------------------------------------------------------------------------------------ //
// CreateInterface.
// This is the primary exported function by a dll, referenced by name via dynamic binding
// that exposes an opaque function pointer to the interface.
//
// We have the Internal variant so Sys_GetFactoryThis() returns the correct internal
// symbol under GCC/Linux/Mac as CreateInterface is DLL_EXPORT so its global so the loaders
// on those OS's pick exactly 1 of the CreateInterface symbols to be the one that is process wide and
// all Sys_GetFactoryThis() calls find that one, which doesn't work. Using the internal walkthrough here
// makes sure Sys_GetFactoryThis() has the dll specific symbol and GetProcAddress() returns the module specific
// function for CreateInterface again getting the dll specific symbol we need.
// ------------------------------------------------------------------------------------ //
auto CreateInterfaceInternal( const char* const pName, int* pReturnCode ) -> void* {
	for ( const auto* pCur = InterfaceReg::s_InterfaceRegs; pCur; pCur = pCur->m_Next ) {
		if ( strcmp( pCur->m_Name, pName ) == 0 ) {
			if ( pReturnCode ) {
				*pReturnCode = IFACE_OK;
			}
			return pCur->m_CreateFn();
		}
	}

	if ( pReturnCode ) {
		*pReturnCode = IFACE_FAILED;
	}
	return nullptr;
}

auto CreateInterface( const char* pName, int* pReturnCode ) -> void* {
	return CreateInterfaceInternal( pName, pReturnCode );
}


static auto Sys_GetModuleHandle( const char* name ) -> void* {
	if ( not name ) {
		// hmm, how can this be handled under linux... is it even necessary?
		return nullptr;
	}

	#if IsPosix()
		void* handle;
		if ( ( handle = dlopen( name, RTLD_NOW ) ) == nullptr ) {
			printf( "DLOPEN Error:%s\n", dlerror() );
			// couldn't open this file
			return nullptr;
		}

		// read "man dlopen" for details
		// in short dlopen() inc a ref count
		// so dec the ref count by performing the close
		dlclose( handle );
		return handle;
	#elif IsWindows()
		return GetModuleHandle( name );
	#endif
}

//-----------------------------------------------------------------------------
// Purpose: returns a pointer to a function, given a module
// Input  : pModuleName - module name
//			*pName - proc name
//-----------------------------------------------------------------------------
static auto Sys_GetProcAddress( const char* pModuleName, const char* pName ) -> void* {
	auto hModule = reinterpret_cast<HMODULE>( Sys_GetModuleHandle( pModuleName ) );
	return reinterpret_cast<void*>( GetProcAddress( hModule, pName ) );
}

#if IsWindows()
	static auto Sys_GetProcAddress( HMODULE hModule, const char* pName ) -> void* {
		return reinterpret_cast<void*>( GetProcAddress( hModule, pName ) );
	}
#endif

auto Sys_LoadLibrary( const char* pLibraryName, const Sys_Flags flags ) -> HMODULE {
	char str[ 1024 ];
	// Note: DLL_EXT_STRING can be "_srv.so" or "_360.dll".
	//       So be careful when using the V_*Extension* routines...
	const char* pDllStringExtension{ V_GetFileExtension( DLL_EXT_STRING ) };
	const char* pModuleExtension{ pDllStringExtension ? pDllStringExtension - 1 : DLL_EXT_STRING };

	V_strncpy( str, pLibraryName, sizeof( str ) );

	// always force the final extension to be the platform's native extension
	V_SetExtension( str, pModuleExtension, sizeof( str ) );

	V_FixSlashes( str );

	#if IsWindows()
		if ( flags & SYS_NOLOAD ) {
			return GetModuleHandle( pLibraryName );
		}

		return LoadLibraryEx( pLibraryName, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH );
	#elif IsPosix()
		int dlopen_mode = RTLD_NOW;

		if ( flags & SYS_NOLOAD ) {
			dlopen_mode |= RTLD_NOLOAD;
		}

		const auto ret{ reinterpret_cast<HMODULE>( dlopen( str, dlopen_mode ) ) };
		if ( not ret and not (flags & SYS_NOLOAD) ) {
			const char* error = dlerror();
			if ( error and ( strstr( error, "No such file" ) == nullptr or strstr( error, "image not found" ) == nullptr ) ) {
				Warning( "Failed to dlopen `%s`, error=%s\n", str, error );
			}
		}

		return ret;
	#endif
}
static bool s_bRunningWithDebugModules{ false };


auto Sys_LoadModule( const char* pModuleName, const Sys_Flags flags ) -> CSysModule* {
	// If using the Steam filesystem, either the DLL must be a minimum footprint
	// file in the depot (MFP) or a filesystem GetLocalCopy() call must be made
	// prior to the call to this routine.
	char cwd[1024] { };
	HMODULE dll{ 0 };

	// always load with a full path
	if ( not V_IsAbsolutePath( pModuleName ) ) {
		// was passed in a relative path, use the current working dir as base for it
		_getcwd( cwd, sizeof( cwd ) );
		const size_t cwdLen{ strlen( cwd ) };
		if ( cwd[ cwdLen - 1 ] == '/' or cwd[ cwdLen - 1 ] == '\\' ) {
			cwd[ cwdLen - 1 ] = 0;
		}

		// ensure inside /bin directory
		char absolutePath[1024] { };
		if ( strstr( pModuleName, "bin/" ) == pModuleName or ( cwd[ cwdLen - 1 ] == 'n' and cwd[ cwdLen - 2 ] == 'i' and cwd[ cwdLen - 3 ] == 'b' ) ) {
			// don't make bin/bin path
			snprintf( absolutePath, sizeof( absolutePath ), "%s/%s", cwd, pModuleName );
		} else {
			snprintf( absolutePath, sizeof( absolutePath ), "%s/bin/%s", cwd, pModuleName );
		}
		dll = Sys_LoadLibrary( absolutePath, flags );
	}

	if ( not dll ) {
		// full path failed, let LoadLibrary() try to search the PATH now
		dll = Sys_LoadLibrary( pModuleName, flags );
	}

	#if !IsLinux()
		// If running in the debugger, assume debug binaries are okay, otherwise they must run with -allowdebug
		if ( Sys_GetProcAddress( dll, "BuiltDebug" ) ) {
			if ( dll and not CommandLine()->FindParm( "-allowdebug" ) and not Plat_IsInDebugSession() ) {
				Error( "Module %s is a debug build\n", pModuleName );
			}

			DevWarning( "Module %s is a debug build\n", pModuleName );

			if ( not s_bRunningWithDebugModules ) {
				s_bRunningWithDebugModules = true;

				#if 0// IsWindows() && IsPC()
					char chMemoryName[ MAX_PATH ];
					DebugKernelMemoryObjectName( chMemoryName );

					(void) CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, chMemoryName );
					// Created a shared memory kernel object specific to process id
					// Existence of this object indicates that we have debug modules loaded
				#endif
			}
		}
	#endif

	return reinterpret_cast<CSysModule*>( dll );
}

auto Sys_LastErrorString() -> const char* {
	static char err[ 2048 ];
	#if IsWindows()
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),// Default language
			reinterpret_cast<LPTSTR>( &lpMsgBuf ),
			0,
			NULL );

		strncpy( err, reinterpret_cast<char*>( lpMsgBuf ), sizeof( err ) );
		LocalFree( lpMsgBuf );
	#elif IsLinux()
		strncpy( err, strerror( errno ), sizeof( err ) );
	#endif

	err[ sizeof( err ) - 1 ] = 0;

	return err;
}


//-----------------------------------------------------------------------------
// Purpose: Determine if any debug modules were loaded
//-----------------------------------------------------------------------------
auto Sys_RunningWithDebugModules() -> bool {
	if ( not s_bRunningWithDebugModules ) {
		#if 0// IsWindows() && IsPC()
				char chMemoryName[ MAX_PATH ];
				DebugKernelMemoryObjectName( chMemoryName );

				HANDLE hObject = OpenFileMapping( FILE_MAP_READ, false, chMemoryName );
				if ( hObject && hObject != INVALID_HANDLE_VALUE )
				{
					CloseHandle( hObject );
					s_bRunningWithDebugModules = true;
				}
		#endif
	}
	return s_bRunningWithDebugModules;
}

auto Sys_UnloadModule( CSysModule* pModule ) -> void {
	if ( not pModule ) {
		return;
	}

	#if IsWindows()
		FreeLibrary( reinterpret_cast<HMODULE>( pModule ) );
	#elif IsPosix()
		dlclose( pModule );
	#endif
}

//-----------------------------------------------------------------------------
// Purpose: returns a pointer to a function, given a module
// Input  : module - windows HMODULE from Sys_LoadModule()
//			*pName - proc name
// Output : factory for this module
//-----------------------------------------------------------------------------
auto Sys_GetFactory( CSysModule* pModule ) -> CreateInterfaceFn {
	if ( not pModule ) {
		return nullptr;
	}

	#if IsWindows()
		return reinterpret_cast<CreateInterfaceFn>( GetProcAddress( reinterpret_cast<HMODULE>( pModule ), CREATEINTERFACE_PROCNAME ) );
	#else
		return reinterpret_cast<CreateInterfaceFn>( dlsym( pModule, CREATEINTERFACE_PROCNAME ) );
	#endif
}

//-----------------------------------------------------------------------------
// Purpose: returns the instance of this module
// Output : interface_instance_t
//-----------------------------------------------------------------------------
auto Sys_GetFactoryThis() -> CreateInterfaceFn {
	return &CreateInterfaceInternal;
}

//-----------------------------------------------------------------------------
// Purpose: returns the instance of the named module
// Input  : *pModuleName - name of the module
// Output : interface_instance_t - instance of that module
//-----------------------------------------------------------------------------
auto Sys_GetFactory( const char* pModuleName ) -> CreateInterfaceFn {
	return reinterpret_cast<CreateInterfaceFn>( Sys_GetProcAddress( pModuleName, CREATEINTERFACE_PROCNAME ) );
}

//-----------------------------------------------------------------------------
// Purpose: get the interface for the specified module and version
// Input  :
// Output :
//-----------------------------------------------------------------------------
auto Sys_LoadInterface( const char* pModuleName, const char* pInterfaceVersionName, CSysModule** pOutModule, void** pOutInterface ) -> bool {
	CSysModule* pMod = Sys_LoadModule( pModuleName );
	if ( not pMod ) {
		return false;
	}

	const CreateInterfaceFn fn = Sys_GetFactory( pMod );
	if ( not fn ) {
		Sys_UnloadModule( pMod );
		return false;
	}

	*pOutInterface = fn( pInterfaceVersionName, nullptr );
	if ( not *pOutInterface ) {
		Sys_UnloadModule( pMod );
		return false;
	}

	if ( pOutModule ) {
		*pOutModule = pMod;
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Place this as a singleton at module scope (e.g.) and use it to get the factory from the specified module name.
//
// When the singleton goes out of scope (.dll unload if at module scope),
//  then it'll call Sys_UnloadModule on the module so that the refcount is decremented
//  and the .dll actually can unload from memory.
//-----------------------------------------------------------------------------
CDllDemandLoader::CDllDemandLoader( char const* pchModuleName )
	: m_pchModuleName( pchModuleName ) { }

CDllDemandLoader::~CDllDemandLoader() {
	Unload();
}

auto CDllDemandLoader::GetFactory() -> CreateInterfaceFn {
	if ( not m_hModule and not m_bLoadAttempted ) {
		m_bLoadAttempted = true;
		m_hModule = Sys_LoadModule( m_pchModuleName );
	}

	if ( not m_hModule ) {
		return nullptr;
	}

	return Sys_GetFactory( m_hModule );
}

auto CDllDemandLoader::Unload() -> void {
	if ( m_hModule ) {
		Sys_UnloadModule( m_hModule );
		m_hModule = nullptr;
	}
}


#if defined( STAGING_ONLY ) && IsWindows()
	typedef USHORT( WINAPI RtlCaptureStackBackTrace_FUNC )( ULONG frames_to_skip, ULONG frames_to_capture, PVOID* backtrace, PULONG backtrace_hash );

	extern "C" int backtrace( void** buffer, int size ) {
		HMODULE hNTDll = GetModuleHandleA( "ntdll.dll" );
		static RtlCaptureStackBackTrace_FUNC* const pfnRtlCaptureStackBackTrace =
			(RtlCaptureStackBackTrace_FUNC*) GetProcAddress( hNTDll, "RtlCaptureStackBackTrace" );

		if ( not pfnRtlCaptureStackBackTrace ) {
			return 0;
		}

		return (int) pfnRtlCaptureStackBackTrace( 2, size, buffer, 0 );
	}
#endif
