//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Define the interface convention used in the valve engine.
//
// $NoKeywords: $
//
//=============================================================================//

// To make an interface and expose it:
//    1. The interface must be ALL pure virtuals, and have no data members.
//    2. Define a name for it.
//    3. In its implementation file, use EXPOSE_INTERFACE or EXPOSE_SINGLE_INTERFACE.

// Versioning
// There are two versioning cases that are handled by this:
// 1. You add functions to the end of an interface, so it is binary compatible with the previous interface. In this case,
//    you need two EXPOSE_INTERFACEs: one to expose your class as the old interface and one to expose it as the new interface.
// 2. You update an interface so it's not compatible anymore (but you still want to be able to expose the old interface
//    for legacy code). In this case, you need to make a new version name for your new interface, and make a wrapper interface and
//    expose it for the old interface.

// Static Linking:
// Must mimic unique seperate class 'InterfaceReg' constructors per subsystem.
// Each subsystem can then import and export interfaces as expected.
// This is achieved through unique namespacing 'InterfaceReg' via symbol _SUBSYSTEM.
// Static Linking also needs to generate unique symbols per interface so as to
// provide a 'stitching' method whereby these interface symbols can be referenced
// via the lib's primary module (usually the lib's interface exposure)
// therby stitching all of that lib's code/data together for eventual final exe link inclusion.
#pragma once
// TODO: move interface.cpp into tier0 library.
#include "tier0/platform.h"

// All interfaces derive from this.
class IBaseInterface {
public:
	virtual ~IBaseInterface() = default;
};

static constexpr auto CREATEINTERFACE_PROCNAME = "CreateInterface";

using CreateInterfaceFn = void*(*)( const char* pName, int* pReturnCode );
using InstantiateInterfaceFn = void*(*)();

// Used internally to register classes.
class InterfaceReg {
public:
	InterfaceReg( InstantiateInterfaceFn fn, const char* pName );

private:
	friend void* CreateInterfaceInternal( const char* name, int* result );

	InstantiateInterfaceFn m_CreateFn;
	const char* m_Name;

	InterfaceReg* m_Next;// For the global list.
	static InterfaceReg* s_InterfaceRegs;
};

// Use these to expose an interface that can have multiple instances.
// e.g.:
// EXPOSE_INTERFACE( CInterfaceImp, IInterface, "MyInterface001" )
// This will expose a class called CInterfaceImp that implements IInterface (a pure class)
// clients can receive a pointer to this class by calling CreateInterface( "MyInterface001" )
//
// In practice, the shared header file defines the interface (IInterface) and version name ("MyInterface001")
// so that each component can use these names/vtables to communicate
//
// A single class can support multiple interfaces through multiple inheritance

// Use this if you want to write the factory function.
#define EXPOSE_INTERFACE_FN( functionName, ifaceName, versionName ) \
	static InterfaceReg __g_Create##ifaceName##_reg( functionName, versionName );

// Used to expose an implementation of an interface which may be instantiated multiple times.
#define EXPOSE_INTERFACE( className, ifaceName, versionName ) \
	static_assert( std::is_base_of_v<ifaceName, className>, "Class must implement the interface" ); \
	static_assert( std::is_default_constructible_v<className>, "Class must have no other constructor than default" ); \
	static InterfaceReg __g_Create##className##_reg( []() -> void* { return static_cast<ifaceName*>( new className ); }, versionName ); // NOLINT(*-reserved-identifier)

// Use this to expose a singleton interface with a global variable you've created.
#define EXPOSE_SINGLE_INTERFACE_GLOBALVAR( className, ifaceName, versionName, globalVarName ) \
	static_assert( std::is_class_v<decltype( globalVarName )>, "Must be a plain object (not * nor &)" ); \
	static_assert( std::is_base_of_v<ifaceName, className>, "Class must implement the interface" ); \
	static_assert( std::is_default_constructible_v<className>, "Class must have no other constructor than default" ); \
	static InterfaceReg __g_Create##className##ifaceName##_reg( []() -> void* { return static_cast<ifaceName*>( &globalVarName ); }, versionName ); // NOLINT(*-reserved-identifier)

// Use this to expose a singleton interface. This creates the global variable for you automatically.
#define EXPOSE_SINGLE_INTERFACE( className, interfaceName, versionName ) \
	static className __g_##className##_singleton;                        \
	EXPOSE_SINGLE_INTERFACE_GLOBALVAR( className, interfaceName, versionName, __g_##className##_singleton );

// load/unload components
class CSysModule;

// interface return status
enum {
	IFACE_OK = 0,
	IFACE_FAILED
};

//-----------------------------------------------------------------------------
// This function is automatically exported and allows you to access any interfaces exposed with the above macros.
// if pReturnCode is set, it will return one of the following values (IFACE_OK, IFACE_FAILED)
// extend this for other error conditions/code
//-----------------------------------------------------------------------------
DLL_EXPORT void* CreateInterface( const char* pName, int* pReturnCode );

//-----------------------------------------------------------------------------
// UNDONE: This is obsolete, use the module load/unload/get instead!!!
//-----------------------------------------------------------------------------
extern CreateInterfaceFn Sys_GetFactory( CSysModule* pModule );
extern CreateInterfaceFn Sys_GetFactory( const char* pModuleName );
extern CreateInterfaceFn Sys_GetFactoryThis();

enum Sys_Flags {
	SYS_NOFLAGS = 0x00,
	SYS_NOLOAD = 0x01// no loading, no ref-counting, only returns handle if lib is loaded.
};

//-----------------------------------------------------------------------------
// Load & Unload should be called in exactly one place for each module
// The factory for that module should be passed on to dependent components for
// proper versioning.
//-----------------------------------------------------------------------------
/**
 * Loads a DLL/component from disk and returns a handle to it
 * @param pModuleName filename of the component
 * @param flags
 * @return opaque handle to the module (hides system dependency)
 */
extern CSysModule* Sys_LoadModule( const char* pModuleName, Sys_Flags flags = SYS_NOFLAGS );
/**
 * Unloads a DLL/component
 * @param pModule handle of the module to unload
 */
extern void Sys_UnloadModule( CSysModule* pModule );

/**
 * Returns the last system error in human-readable form.
 * @return statically allocated string with the error (hides system dependency)
 */
const char* Sys_LastErrorString();

// This is a helper function to load a module, get its factory, and get a specific interface.
// You are expected to free all of these things.
// Returns false and cleans up if any of the steps fail.
bool Sys_LoadInterface( const char* pModuleName, const char* pInterfaceVersionName, CSysModule** pOutModule, void** pOutInterface );

//-----------------------------------------------------------------------------
// Purpose: Place this as a singleton at module scope (e.g.) and use it to get the factory from the specified module name.
//
// When the singleton goes out of scope (.dll unload if at module scope),
//  then it'll call Sys_UnloadModule on the module so that the refcount is decremented
//  and the .dll actually can unload from memory.
//-----------------------------------------------------------------------------
class CDllDemandLoader {
public:
	explicit CDllDemandLoader( char const* pchModuleName );
	virtual ~CDllDemandLoader();
	CreateInterfaceFn GetFactory();
	void Unload();

private:
	char const* m_pchModuleName;
	CSysModule* m_hModule{};
	bool m_bLoadAttempted{};
};
