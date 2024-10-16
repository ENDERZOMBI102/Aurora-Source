//
// Created by ENDERZOMBI102 on 12/02/2024.
//
#include "keyvaluessystem.hpp"
#include "tier0/dbg.h"


void CKeyValuesSystem::RegisterSizeofKeyValues( int size ) {
	AssertUnreachable();
}

void* CKeyValuesSystem::AllocKeyValuesMemory( int size ) {
	// FIXME: This should either use a custom allocator,
	//        or to the very least track the allocation sizes (atomically)
	return malloc( size );
}
void CKeyValuesSystem::FreeKeyValuesMemory( void* pMem ) {
	free( pMem );
}

HKeySymbol CKeyValuesSystem::GetSymbolForString( const char* name, bool bCreate ) {
	auto idx{ this->m_SymbolTable.Find( name ) };

	if ( bCreate && !idx.IsValid() )
		idx = this->m_SymbolTable.AddString( name );

	return idx;
}
const char* CKeyValuesSystem::GetStringForSymbol( HKeySymbol symbol ) {
	return this->m_SymbolTable.String( symbol );
}

void CKeyValuesSystem::AddKeyValuesToMemoryLeakList( void* pMem, HKeySymbol pName ) {
	this->m_LeakList.insert({ pMem, pName });
}
void CKeyValuesSystem::RemoveKeyValuesFromMemoryLeakList( void* pMem ) {
	this->m_LeakList.erase( pMem );
}

void CKeyValuesSystem::AddFileKeyValuesToCache( const KeyValues* _kv, const char* resourceName, const char* pathID ) {
	AssertUnreachable();
}
bool CKeyValuesSystem::LoadFileKeyValuesFromCache( KeyValues* _outKv, const char* resourceName, const char* pathID, IBaseFileSystem* filesystem ) const {
	AssertUnreachable();
	return false;
}
void CKeyValuesSystem::InvalidateCache() {
	AssertUnreachable();
}
void CKeyValuesSystem::InvalidateCacheForFile( const char* resourceName, const char* pathID ) {
	AssertUnreachable();
}

CKeyValuesSystem::~CKeyValuesSystem() {
	if (! this->m_LeakList.empty() )
		Warning( "[CKeyValuesSystem] Some memory was leaked!!" );
}

static CKeyValuesSystem g_KeyValueSystem{};
IKeyValuesSystem* KeyValuesSystem() {
	return &g_KeyValueSystem;
}

