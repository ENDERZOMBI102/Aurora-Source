//
// Created by ENDERZOMBI102 on 08/02/2024.
//
#pragma once
#include "vstdlib/cvar.h"


class CCvarSystem : public ICvar {
public:  // IAppSystem
	auto Connect( CreateInterfaceFn factory ) -> bool override;
	auto Disconnect() -> void override;
	auto QueryInterface( const char* pInterfaceName ) -> void* override;
	auto Init() -> InitReturnVal_t override;
	auto Shutdown() -> void override;
public:  // ICvar
	// Allocate a unique DLL identifier
	auto AllocateDLLIdentifier() -> CVarDLLIdentifier_t override;

	// Register, unregister commands
	auto RegisterConCommand( ConCommandBase* pCommandBase ) -> void override;
	auto UnregisterConCommand( ConCommandBase* pCommandBase ) -> void override;
	auto UnregisterConCommands( CVarDLLIdentifier_t id ) -> void override;

	// If there is a +<varname> <value> on the command line, this returns the value.
	// Otherwise, it returns NULL.
	auto GetCommandLineValue( const char* pVariableName ) -> const char* override;

	// Try to find the cvar pointer by name
	auto FindCommandBase( const char* name ) -> ConCommandBase* override;
	auto FindCommandBase( const char* name ) const -> const ConCommandBase* override;
	auto FindVar( const char* var_name ) -> ConVar* override;
	auto FindVar( const char* var_name ) const -> const ConVar* override;
	auto FindCommand( const char* name ) -> ConCommand* override;
	auto FindCommand( const char* name ) const -> const ConCommand* override;

	// Get first ConCommandBase to allow iteration
	auto GetCommands() -> ConCommandBase* override;
	auto GetCommands() const -> const ConCommandBase* override;

	// Install a global change callback (to be called when any convar changes)
	auto InstallGlobalChangeCallback( FnChangeCallback_t callback ) -> void override;
	auto RemoveGlobalChangeCallback( FnChangeCallback_t callback ) -> void override;
	auto CallGlobalChangeCallbacks( ConVar* var, const char* pOldString, float flOldValue ) -> void override;

	// Install a console printer
	auto InstallConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) -> void override;
	auto RemoveConsoleDisplayFunc( IConsoleDisplayFunc* pDisplayFunc ) -> void override;
	auto ConsoleColorPrintf( const Color& clr, PRINTF_FORMAT_STRING const char* pFormat, ... ) const -> void override FMTFUNCTION( 3, 4 );
	auto ConsolePrintf( PRINTF_FORMAT_STRING const char* pFormat, ... ) const -> void override FMTFUNCTION( 2, 3 );
	auto ConsoleDPrintf( PRINTF_FORMAT_STRING const char* pFormat, ... ) const -> void override FMTFUNCTION( 2, 3 );

	// Reverts cvars which contain a specific flag
	auto RevertFlaggedConVars( int nFlag ) -> void override;

	// Method allowing the engine ICvarQuery interface to take over
	// A little hacky, owing to the fact the engine is loaded
	// well after ICVar, so we can't use the standard connect pattern
	auto InstallCVarQuery( ICvarQuery* pQuery ) -> void override;

	auto IsMaterialThreadSetAllowed() const -> bool override;
	auto QueueMaterialThreadSetValue( ConVar* pConVar, const char* pValue ) -> void override;
	auto QueueMaterialThreadSetValue( ConVar* pConVar, int nValue ) -> void override;
	auto QueueMaterialThreadSetValue( ConVar* pConVar, float flValue ) -> void override;
	auto HasQueuedMaterialThreadConVarSets() const -> bool override;
	auto ProcessQueuedMaterialThreadConVarSets() -> int override;
protected:
	// internals for  ICVarIterator
	class CCVarSystemIterator final : public ICVarIteratorInternal {
	public:
		// warning: delete called on 'ICvar::ICVarIteratorInternal' that is abstract but has non-virtual destructor [-Wdelete-non-virtual-dtor]
		~CCVarSystemIterator() override = default;
		auto SetFirst() -> void override;
		auto Next() -> void override;
		auto IsValid() -> bool override;
		auto Get() -> ConCommandBase* override;
	};

	auto FactoryInternalIterator() -> ICVarIteratorInternal* override;
protected:
	friend class Iterator;
private:
	int m_IdCounter{ 0 };
};
