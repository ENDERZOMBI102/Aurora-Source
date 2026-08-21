//
// Created by ENDERZOMBI102 on 09/02/2024.
//
#include "cvarsystem.hpp"
#include "tier1/convar.h"
#include "tier0/icommandline.h"
#include "Color.h"
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
	AssertMsg( false, "CCvarSystem::RegisterConCommand(%p)\n", pCommandBase );
}
auto CCvarSystem::UnregisterConCommand( ConCommandBase* pCommandBase ) -> void {
	AssertMsg( false, "CCvarSystem::UnregisterConCommand(%p)\n", pCommandBase );
}
auto CCvarSystem::UnregisterConCommands( CVarDLLIdentifier_t id ) -> void {
	AssertMsg( false, "CCvarSystem::UnregisterConCommands(%d)\n", id );
}

auto CCvarSystem::GetCommandLineValue( const char* pVariableName ) -> const char* {
	char cla[256] {};
	V_sprintf_safe( cla, "+%s", pVariableName );
	return CommandLine()->ParmValue( cla, nullptr );
}

auto CCvarSystem::FindCommandBase( const char* name ) -> ConCommandBase* {
	AssertMsg( false, "CCvarSystem::FindCommandBase(%s)\n", name );
	return {};
}
auto CCvarSystem::FindCommandBase( const char* name ) const -> const ConCommandBase* {
	AssertMsg( false, "CCvarSystem::FindCommandBase(%s) const\n", name );
	return {};
}
auto CCvarSystem::FindVar( const char* var_name ) -> ConVar* {
	AssertMsg( false, "CCvarSystem::FindVar(%s)\n", var_name );
	return {};
}
auto CCvarSystem::FindVar( const char* var_name ) const -> const ConVar* {
	AssertMsg( false, "CCvarSystem::FindVar(%s) const\n", var_name );
	return {};
}
auto CCvarSystem::FindCommand( const char* name ) -> ConCommand* {
	AssertMsg( false, "CCvarSystem::FindCommand(%s)\n", name );
	return {};
}
auto CCvarSystem::FindCommand( const char* name ) const -> const ConCommand* {
	AssertMsg( false, "CCvarSystem::FindCommand(%s) const\n", name );
	return {};
}

auto CCvarSystem::GetCommands() -> ConCommandBase* {
	AssertMsg( false, "CCvarSystem::GetCommands()\n" );
	return {};
}
auto CCvarSystem::GetCommands() const -> const ConCommandBase* {
	AssertMsg( false, "CCvarSystem::GetCommands() const\n" );
	return {};
}

auto CCvarSystem::InstallGlobalChangeCallback( FnChangeCallback_t callback ) -> void {
	AssertMsg( false, "CCvarSystem::InstallGlobalChangeCallback(%p)\n", callback );
}
auto CCvarSystem::RemoveGlobalChangeCallback( FnChangeCallback_t callback ) -> void {
	AssertMsg( false, "CCvarSystem::RemoveGlobalChangeCallback(%p)\n", callback );
}
auto CCvarSystem::CallGlobalChangeCallbacks( ConVar* var, const char* pOldString, float flOldValue ) -> void {
	AssertMsg( false, "CCvarSystem::CallGlobalChangeCallbacks(%p, `%s`, `%f`)\n", var, pOldString, flOldValue );
}

auto CCvarSystem::InstallConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) -> void {
	AssertMsg( false, "CCvarSystem::InstallConsoleDisplayFunc(%p)\n", pDisplayFunc );
}
auto CCvarSystem::RemoveConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) -> void {
	AssertMsg( false, "CCvarSystem::RemoveConsoleDisplayFunc(%p)\n", pDisplayFunc );
}
auto CCvarSystem::ConsoleColorPrintf( const Color& clr, const char* pFormat, ... ) const -> void {
	AssertMsg( false, "CCvarSystem::ConsoleColorPrintf(%x, `%s`)\n", clr.GetRawColor(), pFormat );
}
auto CCvarSystem::ConsolePrintf( const char* pFormat, ... ) const -> void {
	AssertMsg( false, "CCvarSystem::ConsolePrintf(%s)\n", pFormat );
}
auto CCvarSystem::ConsoleDPrintf( const char* pFormat, ... ) const -> void {
	AssertMsg( false, "CCvarSystem::ConsoleDPrintf(%s)\n", pFormat );
}

auto CCvarSystem::RevertFlaggedConVars( int nFlag ) -> void {
	AssertMsg( false, "CCvarSystem::RevertFlaggedConVars(%d)\n", nFlag );
}

auto CCvarSystem::InstallCVarQuery( ICvarQuery* pQuery ) -> void {
	AssertMsg( false, "CCvarSystem::InstallCVarQuery(%p)\n", pQuery );
}

auto CCvarSystem::IsMaterialThreadSetAllowed() const -> bool {
	AssertMsg( false, "CCvarSystem::IsMaterialThreadSetAllowed()\n" );
	return {};
}
auto CCvarSystem::QueueMaterialThreadSetValue( ConVar* pConVar, const char* pValue ) -> void {
	AssertMsg( false, "CCvarSystem::QueueMaterialThreadSetValue(%p, %s)\n", pConVar, pValue );
}
auto CCvarSystem::QueueMaterialThreadSetValue( ConVar* pConVar, int nValue ) -> void {
	AssertMsg( false, "CCvarSystem::QueueMaterialThreadSetValue(%p, %d)\n", pConVar, nValue );
}
auto CCvarSystem::QueueMaterialThreadSetValue( ConVar* pConVar, float flValue ) -> void {
	AssertMsg( false, "CCvarSystem::QueueMaterialThreadSetValue(%p, %f)\n", pConVar, flValue );
}
auto CCvarSystem::HasQueuedMaterialThreadConVarSets() const -> bool {
	AssertMsg( false, "CCvarSystem::HasQueuedMaterialThreadConVarSets()\n" );
	return {};
}
auto CCvarSystem::ProcessQueuedMaterialThreadConVarSets() -> int {
	AssertMsg( false, "CCvarSystem::ProcessQueuedMaterialThreadConVarSets()\n" );
	return {};
}

auto CCvarSystem::FactoryInternalIterator() -> ICVarIteratorInternal* {
	return new CCVarSystemIterator{};
}

auto CCvarSystem::CCVarSystemIterator::SetFirst() -> void {
	AssertMsg( false, "CCvarSystem::CCVarSystemIterator::SetFirst()" );
}
auto CCvarSystem::CCVarSystemIterator::Next() -> void {
	AssertMsg( false, "CCvarSystem::CCVarSystemIterator::Next()" );
}
auto CCvarSystem::CCVarSystemIterator::IsValid() -> bool {
	AssertMsg( false, "CCvarSystem::CCVarSystemIterator::IsValid()" );
	return {};
}
auto CCvarSystem::CCVarSystemIterator::Get() -> ConCommandBase* {
	AssertMsg( false, "CCvarSystem::CCVarSystemIterator::Get()" );
	return {};
}

namespace { CCvarSystem s_CvarSystem{}; }
EXPOSE_SINGLE_INTERFACE_GLOBALVAR_T( CCvarSystem, ICvar, s_CvarSystem )

CON_COMMAND( find, "Find concommands with the specified string in their name/help text." ) {

}
