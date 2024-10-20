//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once
#include "const.h"
#include "tier0/dbg.h"

class IHandleEntity;

// -------------------------------------------------------------------------------------------------- //
// CBaseHandle.
// -------------------------------------------------------------------------------------------------- //

class CBaseHandle {
	friend class CBaseEntityList;
public:
	CBaseHandle() = default;
	CBaseHandle( const CBaseHandle& other );
	CBaseHandle( unsigned long value ); // NOLINT(*-explicit-constructor)
	CBaseHandle( int iEntry, int iSerialNumber );

	void Init( int iEntry, int iSerialNumber );
	void Term();

	// Even if this returns true, Get() still can return return a non-null value.
	// This just tells if the handle has been initted with any values.
	[[nodiscard]]
	bool IsValid() const;

	[[nodiscard]]
	int GetEntryIndex() const;
	[[nodiscard]]
	int GetSerialNumber() const;

	[[nodiscard]]
	int ToInt() const;
	bool operator!=( const CBaseHandle& other ) const;
	bool operator==( const CBaseHandle& other ) const;
	bool operator==( const IHandleEntity* pEnt ) const;
	bool operator!=( const IHandleEntity* pEnt ) const;
	bool operator<( const CBaseHandle& other ) const;
	bool operator<( const IHandleEntity* pEnt ) const;

	// Assign a value to the handle.
	const CBaseHandle& operator=( const IHandleEntity* pEntity );
	const CBaseHandle& Set( const IHandleEntity* pEntity );

	// Use this to dereference the handle.
	// Note: this is implemented in game code (ehandle.h)
	[[nodiscard]]
	IHandleEntity* Get() const;
protected:
	// The low NUM_SERIAL_BITS hold the index. If this value is less than MAX_EDICTS, then the entity is networkable.
	// The high NUM_SERIAL_NUM_BITS bits are the serial number.
	unsigned long m_Index{ INVALID_EHANDLE_INDEX };
};


#include "ihandleentity.h"


inline CBaseHandle::CBaseHandle( const CBaseHandle& other ) {
	m_Index = other.m_Index;
}

inline CBaseHandle::CBaseHandle( unsigned long value ) {
	m_Index = value;
}

inline CBaseHandle::CBaseHandle( int iEntry, int iSerialNumber ) {
	Init( iEntry, iSerialNumber );
}

inline void CBaseHandle::Init( int iEntry, int iSerialNumber ) {
	Assert( iEntry >= 0 && iEntry < NUM_ENT_ENTRIES );
	Assert( iSerialNumber >= 0 && iSerialNumber < ( 1 << NUM_SERIAL_NUM_BITS ) );

	m_Index = iEntry | ( iSerialNumber << NUM_ENT_ENTRY_BITS );
}

inline void CBaseHandle::Term() {
	m_Index = INVALID_EHANDLE_INDEX;
}

inline bool CBaseHandle::IsValid() const {
	return m_Index != INVALID_EHANDLE_INDEX;
}

inline int CBaseHandle::GetEntryIndex() const {
	return static_cast<int>( m_Index & ENT_ENTRY_MASK );
}

inline int CBaseHandle::GetSerialNumber() const {
	return static_cast<int>( m_Index >> NUM_ENT_ENTRY_BITS );
}

inline int CBaseHandle::ToInt() const {
	return static_cast<int>( m_Index );
}

inline bool CBaseHandle::operator!=( const CBaseHandle& other ) const {
	return m_Index != other.m_Index;
}

inline bool CBaseHandle::operator==( const CBaseHandle& other ) const {
	return m_Index == other.m_Index;
}

inline bool CBaseHandle::operator==( const IHandleEntity* pEnt ) const {
	return Get() == pEnt;
}

inline bool CBaseHandle::operator!=( const IHandleEntity* pEnt ) const {
	return Get() != pEnt;
}

inline bool CBaseHandle::operator<( const CBaseHandle& other ) const {
	return m_Index < other.m_Index;
}

inline bool CBaseHandle::operator<( const IHandleEntity* pEntity ) const {
	unsigned long otherIndex = ( pEntity ) ? pEntity->GetRefEHandle().m_Index : INVALID_EHANDLE_INDEX;
	return m_Index < otherIndex;
}

inline const CBaseHandle& CBaseHandle::operator=( const IHandleEntity* pEntity ) {
	return Set( pEntity );
}

inline const CBaseHandle& CBaseHandle::Set( const IHandleEntity* pEntity ) {
	if ( pEntity ) {
		*this = pEntity->GetRefEHandle();
	} else {
		m_Index = INVALID_EHANDLE_INDEX;
	}

	return *this;
}
