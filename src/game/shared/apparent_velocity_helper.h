//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once


inline float CalcDistance( float x, float y ) {
	return x - y;
}

inline float CalcDistance( const Vector& a, const Vector& b ) {
	return a.DistTo( b );
}


template<class T>
class CDefaultCalcDistance {
public:
	static inline float CalcDistance( const T& a, const T& b ) {
		return ::CalcDistance( a, b );
	}
};

class CCalcDistance2D {
public:
	static inline float CalcDistance( const Vector& a, const Vector& b ) {
		return ( a - b ).Length2D();
	}
};


template<class T, class Functor = CDefaultCalcDistance<T>>
class CApparentVelocity {
public:
	CApparentVelocity( const T& t0 ) {
		m_LastTime = -1;
		m_LastValue = t0;
	}

	float AddSample( float time, T value ) {
		float flRet = 0;
		if ( m_LastTime != -1 ) {
			flRet = Functor::CalcDistance( value, m_LastValue ) / ( time - m_LastTime );
		}

		m_LastTime = time;
		m_LastValue = value;

		return flRet;
	}

private:
	T m_LastValue;
	float m_LastTime;
};
