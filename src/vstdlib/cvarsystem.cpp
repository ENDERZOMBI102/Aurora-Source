//
// Created by ENDERZOMBI102 on 09/02/2024.
//
#include "cvarsystem.hpp"

#include "tier1/convar.h"
// This must be the final include in a .cpp file!!!
#include "memdbgon.h"


// --- IAppSystem ---
auto CCvarSystem::Connect( CreateInterfaceFn factory ) -> bool {
	return true;
}
auto CCvarSystem::Disconnect() -> void { }
auto CCvarSystem::QueryInterface( const char* pInterfaceName ) -> void* {
	if ( V_strcmp( pInterfaceName, ICvar::INTERFACE_VERSION ) == 0 ) {
		return this;
	}
	return nullptr;
}
auto CCvarSystem::Init() -> InitReturnVal_t {
	return INIT_OK;
}
auto CCvarSystem::Shutdown() -> void { }

// --- CVvarSystem ---
auto CCvarSystem::AllocateDLLIdentifier() -> CVarDLLIdentifier_t {
	const int32 id{ m_IdCounter };
	m_IdCounter += 1;
	return id;
}

auto CCvarSystem::RegisterConCommand( ConCommandBase* pCommandBase ) -> void {
}
auto CCvarSystem::UnregisterConCommand( ConCommandBase* pCommandBase ) -> void {
}
auto CCvarSystem::UnregisterConCommands( CVarDLLIdentifier_t id ) -> void {
}

auto CCvarSystem::GetCommandLineValue( const char* pVariableName ) -> const char* {
}

auto CCvarSystem::FindCommandBase( const char* name ) -> ConCommandBase* {
}
auto CCvarSystem::FindCommandBase( const char* name ) const -> const ConCommandBase* {
}
auto CCvarSystem::FindVar( const char* var_name ) -> ConVar* {
}
auto CCvarSystem::FindVar( const char* var_name ) const -> const ConVar* {
}
auto CCvarSystem::FindCommand( const char* name ) -> ConCommand* {
}
auto CCvarSystem::FindCommand( const char* name ) const -> const ConCommand* {
}

auto CCvarSystem::GetCommands() -> ConCommandBase* {
}
auto CCvarSystem::GetCommands() const -> const ConCommandBase* {
}

auto CCvarSystem::InstallGlobalChangeCallback( FnChangeCallback_t callback ) -> void {
}
auto CCvarSystem::RemoveGlobalChangeCallback( FnChangeCallback_t callback ) -> void {
}
auto CCvarSystem::CallGlobalChangeCallbacks( ConVar* var, const char* pOldString, float flOldValue ) -> void {
}

auto CCvarSystem::InstallConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) -> void {
}
auto CCvarSystem::RemoveConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) -> void {
}
auto CCvarSystem::ConsoleColorPrintf( const Color& clr, const char* pFormat, ... ) const -> void {
}
auto CCvarSystem::ConsolePrintf( const char* pFormat, ... ) const -> void {
}
auto CCvarSystem::ConsoleDPrintf( const char* pFormat, ... ) const -> void {
}

auto CCvarSystem::RevertFlaggedConVars( int nFlag ) -> void {
}

auto CCvarSystem::InstallCVarQuery( ICvarQuery* pQuery ) -> void {
}

auto CCvarSystem::IsMaterialThreadSetAllowed() const -> bool {
}
auto CCvarSystem::QueueMaterialThreadSetValue( ConVar* pConVar, const char* pValue ) -> void {
}
auto CCvarSystem::QueueMaterialThreadSetValue( ConVar* pConVar, int nValue ) -> void {
}
auto CCvarSystem::QueueMaterialThreadSetValue( ConVar* pConVar, float flValue ) -> void {
}
auto CCvarSystem::HasQueuedMaterialThreadConVarSets() const -> bool {
}
auto CCvarSystem::ProcessQueuedMaterialThreadConVarSets() -> int {
}

auto CCvarSystem::FactoryInternalIterator() -> ICVarIteratorInternal* {
	return new CCVarSystemIterator{};
}

auto CCvarSystem::CCVarSystemIterator::SetFirst() -> void {
}
auto CCvarSystem::CCVarSystemIterator::Next() -> void {
}
auto CCvarSystem::CCVarSystemIterator::IsValid() -> bool {
}
auto CCvarSystem::CCVarSystemIterator::Get() -> ConCommandBase* {
}

namespace { CCvarSystem s_CvarSystem{}; }
EXPOSE_SINGLE_INTERFACE_GLOBALVAR_T( CCvarSystem, ICvar, s_CvarSystem )

CON_COMMAND( find, "Find concommands with the specified string in their name/help text." ) {

}
