//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Contains general purpose macros that are appropriate for use
//          in engine/launcher/all tools.
//
// $NoKeywords: $
//
//=============================================================================//
#pragma once

// Makes a 4-byte "packed ID" int out of 4 characters
#define MAKEID( $d, $c, $b, $a ) ( ( (int) ( $a ) << 24 ) | ( (int) ( $b ) << 16 ) | ( (int) ( $c ) << 8 ) | ( (int) ( $d ) ) )
/// Like [MAKEID], but reversed and with uint32 instead of int32
#define MAKEID_REV( $a, $b, $c, $d ) ( ( (uint32) ( $a ) << 24 ) | ( (uint32) ( $b ) << 16 ) | ( (uint32) ( $c ) << 8 ) | ( (uint32) ( $d ) ) )

// Compares a string with a 4-byte packed ID constant
#define STRING_MATCHES_ID( p, id ) ( ( *( (int*) ( p ) ) == ( id ) ) ? true : false )
#define ID_TO_STRING( id, p ) ( ( p )[ 3 ] = ( ( ( id ) >> 24 ) & 0xFF ), ( p )[ 2 ] = ( ( ( id ) >> 16 ) & 0xFF ), ( p )[ 1 ] = ( ( ( id ) >> 8 ) & 0xFF ), ( p )[ 0 ] = ( ( ( id ) >> 0 ) & 0xFF ) )

#define SETBITS( iBitVector, bits ) ( ( iBitVector ) |= ( bits ) )
#define CLEARBITS( iBitVector, bits ) ( ( iBitVector ) &= ~( bits ) )
#define FBitSet( iBitVector, bits ) ( ( iBitVector ) & ( bits ) )

template<typename T>
inline bool IsPowerOfTwo( T value ) {
	return ( value & ( value - (T) 1 ) ) == (T) 0;
}

#ifndef REFERENCE
	#define REFERENCE( arg ) ( (void) arg )
#endif

#ifndef NOTE_UNUSED
	// for pesky compiler / lint warnings
	#define NOTE_UNUSED( x ) (void)(x)
#endif


// Using ARRAYSIZE implementation from winnt.h:
#ifdef ARRAYSIZE
	#undef ARRAYSIZE
#endif

// ARRAYSIZE is more readable version of RTL_NUMBER_OF_V2
// _ARRAYSIZE is a version useful for anonymous types
#define ARRAYSIZE( A ) ( sizeof( A ) / sizeof( ( A )[ 0 ] ) )
#define Q_ARRAYSIZE( p ) ARRAYSIZE( p )

template<typename IndexType, typename T, unsigned int N>
IndexType ClampedArrayIndex( const T (&buffer)[N], IndexType index ) {
	NOTE_UNUSED( buffer );
	return clamp( index, 0, (IndexType) N - 1 );
}

template<typename T, unsigned int N>
T ClampedArrayElement( const T (&buffer)[N], unsigned int uIndex ) {
	// Put index in an unsigned type to halve the clamping.
	if ( uIndex >= N ) {
		uIndex = N - 1;
	}
	return buffer[ uIndex ];
}
