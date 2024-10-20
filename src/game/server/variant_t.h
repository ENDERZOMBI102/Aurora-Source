//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//
#pragma once
#include "ehandle.h"
#include "mathlib/vmatrix.h"

class CBaseEntity;


//
// A variant class for passing data in entity input/output connections.
//
class variant_t {
	union {
		bool bVal;
		string_t iszVal;
		int iVal;
		float flVal;
		float vecVal[ 3 ];
		Color rgbaVal;
	};
	CHandle<CBaseEntity> eVal;// this can't be in the union because it has a constructor.

	fieldtype_t fieldType;

public:
	// constructor
	variant_t() : fieldType( FIELD_VOID ), iVal( 0 ) {}

	inline bool Bool() const { return ( fieldType == FIELD_BOOLEAN ) && bVal; }
	inline const char* String() const { return ( fieldType == FIELD_STRING ) ? STRING( iszVal ) : ToString(); }
	inline string_t StringID() const { return ( fieldType == FIELD_STRING ) ? iszVal : NULL_STRING; }
	inline int Int() const { return ( fieldType == FIELD_INTEGER ) ? iVal : 0; }
	inline float Float() const { return ( fieldType == FIELD_FLOAT ) ? flVal : 0; }
	inline const CHandle<CBaseEntity>& Entity() const;
	inline Color Color32() const { return rgbaVal; }
	inline void Vector3D( Vector& vec ) const;

	fieldtype_t FieldType() { return fieldType; }

	void SetBool( bool b ) {
		bVal = b;
		fieldType = FIELD_BOOLEAN;
	}
	void SetString( string_t str ) { iszVal = str, fieldType = FIELD_STRING; }
	void SetInt( int val ) { iVal = val, fieldType = FIELD_INTEGER; }
	void SetFloat( float val ) { flVal = val, fieldType = FIELD_FLOAT; }
	void SetEntity( CBaseEntity* val );
	void SetVector3D( const Vector& val ) {
		vecVal[ 0 ] = val[ 0 ];
		vecVal[ 1 ] = val[ 1 ];
		vecVal[ 2 ] = val[ 2 ];
		fieldType = FIELD_VECTOR;
	}
	void SetPositionVector3D( const Vector& val ) {
		vecVal[ 0 ] = val[ 0 ];
		vecVal[ 1 ] = val[ 1 ];
		vecVal[ 2 ] = val[ 2 ];
		fieldType = FIELD_POSITION_VECTOR;
	}
	void SetColor32( Color val ) {
		rgbaVal = val;
		fieldType = FIELD_COLOR32;
	}
	void SetColor32( int r, int g, int b, int a ) {
		rgbaVal.SetColor( r, g, b, a );
		fieldType = FIELD_COLOR32;
	}
	void Set( fieldtype_t ftype, void* data );
	void SetOther( void* data );
	bool Convert( fieldtype_t newType );

	static typedescription_t m_SaveBool[];
	static typedescription_t m_SaveInt[];
	static typedescription_t m_SaveFloat[];
	static typedescription_t m_SaveEHandle[];
	static typedescription_t m_SaveString[];
	static typedescription_t m_SaveColor[];
	static typedescription_t m_SaveVector[];
	static typedescription_t m_SavePositionVector[];
	static typedescription_t m_SaveVMatrix[];
	static typedescription_t m_SaveVMatrixWorldspace[];
	static typedescription_t m_SaveMatrix3x4Worldspace[];

protected:
	//
	// Returns a string representation of the value without modifying the variant.
	//
	const char* ToString() const;

	friend class CVariantSaveDataOps;
};


//-----------------------------------------------------------------------------
// Purpose: Returns this variant as a vector.
//-----------------------------------------------------------------------------
inline void variant_t::Vector3D( Vector& vec ) const {
	if ( ( fieldType == FIELD_VECTOR ) || ( fieldType == FIELD_POSITION_VECTOR ) ) {
		vec[ 0 ] = vecVal[ 0 ];
		vec[ 1 ] = vecVal[ 1 ];
		vec[ 2 ] = vecVal[ 2 ];
	} else {
		vec = vec3_origin;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Returns this variant as an EHANDLE.
//-----------------------------------------------------------------------------
inline const CHandle<CBaseEntity>& variant_t::Entity() const {
	if ( fieldType == FIELD_EHANDLE )
		return eVal;

	static CHandle<CBaseEntity> hNull;
	hNull.Set( nullptr );
	return ( hNull );
}
