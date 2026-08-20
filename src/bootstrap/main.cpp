//
// Created by ENDERZOMBI102 on 14/10/2024.
//
#if defined( PLATFORM_WINDOWS )
	#include <libloaderapi.h>
	#include <winbase.h>
	#include <winuser.h>
	#define EXE_EXT_STRING ".exe"
#elif defined( PLATFORM_POSIX )
	#include <dlfcn.h>
	#define EXE_EXT_STRING ""
#endif


#include <cstdlib>
#include <cstring>
#include <format>
#include <vector>


// This is a trick to get the DLL extension off the -D option on the command line.
#define DLLExtTokenPaste( x ) #x
#define DLLExtTokenPaste2( x ) DLLExtTokenPaste( x )
#define DLL_EXT_STRING DLLExtTokenPaste2( _DLL_EXT )

namespace {
	using LauncherMain_t = int (*)( int, const char** );

	#if defined( PLATFORM_WINDOWS )
		auto Strap_LoadModule( const char* const pszPath ) -> HMODULE {
			return LoadLibraryEx( pszPath, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH );
		}

		auto Strap_GetProcAddress( const HMODULE hHandle, const char* const pszName ) -> auto {
			return GetProcAddress( hHandle, pszName );
		}

		auto Strap_ShowError() -> void {
			char* pszError;
			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr,
				GetLastError(),
				MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
				reinterpret_cast<LPTSTR>( &pszError ),
				0,
				nullptr
			);

			char szBuf[1024];
			_snprintf( szBuf, sizeof( szBuf ), "Failed to load the launcher DLL:\n\n%s", pszError );
			szBuf[sizeof( szBuf ) - 1] = '\0';
			MessageBox( nullptr, szBuf, "Launcher Error", MB_OK );

			LocalFree( pszError );
		}
	#elif defined( PLATFORM_POSIX )
		auto Strap_LoadModule( const char* pszPath ) -> void* {
			return dlopen( pszPath, RTLD_NOW );
		}

		auto Strap_GetProcAddress( void* pHandle, const char* pszName ) -> void* {
			return dlsym( pHandle, pszName );
		}

		auto Strap_ShowError() -> void {
			fprintf( stderr, "Failed to load the launcher DLL: %s\n", dlerror() );
		}
	#endif
}

#if defined( PLATFORM_WINDOWS )
	using DWORD = unsigned long;

	extern "C" {
		// hinting the nvidia driver to use the dedicated graphics card in an optimus configuration
		// for more info, see: https://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
		__declspec(dllexport) DWORD NvOptimusEnablement{ 0x00000001 };

		// same thing for AMD GPUs using v13.35 or newer drivers
		__declspec(dllexport) int AmdPowerXpressRequestHighPerformance{ 1 };
	}
#endif

int main( const int argc, const char** argv ) {
	const char* binName{};
	const char* binDir = ({
		const auto path{ argv[0] };
		const size_t fullLength{ std::strlen( path ) };
		size_t length{ fullLength - 1 };
		while ( length > 0 and not( path[length] == '\\' or path[length] == '/' ) ) {
			length -= 1;
		}

		// bootstrap binary name
		binName = path + length + 1;

		// engine bin directory
		const auto res = new char[length + 2];
		std::memcpy( res, path, length );
		res[length + 0] = '/';
		res[length + 1] = '\0';
		res;
	});

	std::vector<const char*> newArgv{ argc };
	std::copy_n( argv, argc, newArgv.begin() );

	std::string biName{ binName };
	if ( biName != "aurosrc" EXE_EXT_STRING ) {
		biName.erase( biName.length() - strlen( EXE_EXT_STRING ) );
		newArgv.insert( newArgv.begin() + 1, "-game" );
		newArgv.insert( newArgv.begin() + 2, biName.c_str() );
	}

	// on posix-like, set the LD_LIBRARY_PATH such as the other binaries can be found
	#if defined( PLATFORM_POSIX )
		const auto old{ std::getenv( "LD_LIBRARY_PATH" ) };
		// the value is copied, so no need to worry about the tmp object
		setenv( "LD_LIBRARY_PATH", old ? std::format( "{}:{}", binDir, old ).c_str() : binDir, true );
	#endif

	// create absolute launcher dll path
	const auto launcherDll{ std::format( "{}launcher" DLL_EXT_STRING, binDir ) };

	// open launcher dll
	const auto lib{ Strap_LoadModule( launcherDll.c_str() ) };
	if ( not lib ) {
		Strap_ShowError();
		return 1;
	}

	// get hold of the main function
	const auto launcherMain{ reinterpret_cast<LauncherMain_t>( Strap_GetProcAddress( lib, "LauncherMain" ) ) };
	if ( not launcherMain ) {
		Strap_ShowError();
		return 1;
	}

	// call it
	return launcherMain( newArgv.size(), newArgv.data() );
}

