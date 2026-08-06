//
// Created by ENDERZOMBI102 on 31/08/2024.
//
#include "appframework/AppFramework.h"
#include "tier0/icommandline.h"
#include "filesystem_init.h"
#include "vstdlib/cvar.h"
// This must be the final include in a .cpp file!!!
#include "memdbgon.h"


namespace {
	void* s_AppInstance{ nullptr };
}

void* GetAppInstance() {
	return s_AppInstance;
}

void SetAppInstance( void* hInstance ) {
	s_AppInstance = hInstance;
}

int AppMain( void* hInstance, void* hPrevInstance, const char* lpCmdLine, int nCmdShow, CAppSystemGroup* pAppSystemGroup ) {
	CommandLine()->CreateCmdLine( lpCmdLine );
	s_AppInstance = hInstance;
	return pAppSystemGroup->Run();
}
int AppMain( const int argc, char** argv, CAppSystemGroup* pAppSystemGroup ) {
	CommandLine()->CreateCmdLine( argc, argv );
	return pAppSystemGroup->Run();
}

int AppStartup( void* hInstance, void* hPrevInstance, const char* lpCmdLine, int nCmdShow, CAppSystemGroup* pAppSystemGroup ) {
	CommandLine()->CreateCmdLine( lpCmdLine );
	s_AppInstance = hInstance;
	return pAppSystemGroup->Startup();
}
int AppStartup( const int argc, char** argv, CAppSystemGroup* pAppSystemGroup ) {
	CommandLine()->CreateCmdLine( argc, argv );
	return pAppSystemGroup->Startup();
}
void AppShutdown( CAppSystemGroup* pAppSystemGroup ) {
	pAppSystemGroup->Shutdown();
}


// --- CSteamApplication ---
CSteamApplication::CSteamApplication( CSteamAppSystemGroup* pAppSystemGroup )
	: m_pChildAppSystemGroup{ pAppSystemGroup } { }

auto CSteamApplication::Startup() -> int {
	return m_pChildAppSystemGroup->Startup();
}
auto CSteamApplication::Shutdown() -> void {
	m_pChildAppSystemGroup->Shutdown();
}

// CSteamApplication - IAppSystem
auto CSteamApplication::Create() -> bool {
	// load ICVar/cvar
	if ( not AddSystem( LoadModule( VStdLib_GetICVarFactory() ), CVAR_INTERFACE_VERSION ) ) {
		return false;
	}

	// load the fs module
	char fsDllName[1024];
	FileSystem_SetErrorMode( FSErrorMode_t::FS_ERRORMODE_AUTO );
	const auto res{ FileSystem_GetFileSystemDLLName( fsDllName, std::size( fsDllName ), m_bSteam ) };
	if ( res != FSReturnCode_t::FS_OK ) {
		const char* error;
		switch ( fsRetCode ) {
			case FS_INVALID_PARAMETERS: error = "invalid parameters."; break;
			case FS_UNABLE_TO_INIT: error = "unable to find a valid implementation."; break;
			default: AssertUnreachable();
		}
		Warning( "Failed to find filesystem module: %s\n", error );
		return false;
	}
	m_pFileSystem = dynamic_cast<IFileSystem*>( AddSystem( LoadModule( fsDllName ), FILESYSTEM_INTERFACE_VERSION ) );
	if ( not m_pFileSystem ) {
		return false;
	}

	g_pFullFileSystem = m_pFileSystem;

	// give the fs module to the child group, so it can play with it
	m_pChildAppSystemGroup->Setup( m_pFileSystem, this );
	return m_pChildAppSystemGroup->Create();
}
auto CSteamApplication::PreInit() -> bool {
	return m_pChildAppSystemGroup->PreInit();
}
auto CSteamApplication::Main() -> int {
	return m_pChildAppSystemGroup->Main();
}
auto CSteamApplication::PostShutdown() -> void {
	return m_pChildAppSystemGroup->PostShutdown();
}
auto CSteamApplication::Destroy() -> void {
	return m_pChildAppSystemGroup->Destroy();
}
