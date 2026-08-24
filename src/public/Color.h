//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//
#pragma once
#include <type_traits>

//-----------------------------------------------------------------------------
// Purpose: Basic handler for a rgba (32b) set of colors.
//			This class is fully inline.
//-----------------------------------------------------------------------------
class Color {
public:
	// constructors
	constexpr Color() = default;
	constexpr Color( const Color& ) = default;
	explicit Color( const int _color ) {
		this->SetRawColor( _color );
	};
	constexpr Color( const int _r, const int _g, const int _b ) {
		this->SetColor( _r, _g, _b, 0 );
	}
	constexpr Color( const int _r, const int _g, const int _b, const int _a ) {
		this->SetColor( _r, _g, _b, _a );
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	constexpr void SetColor( const int _r, const int _g, const int _b, const int _a = 0 ) {
		this->_color[ 0 ] = static_cast<unsigned char>( _r );
		this->_color[ 1 ] = static_cast<unsigned char>( _g );
		this->_color[ 2 ] = static_cast<unsigned char>( _b );
		this->_color[ 3 ] = static_cast<unsigned char>( _a );
	}

	constexpr void GetColor( int& _r, int& _g, int& _b, int& _a ) const {
		_r = this->_color[ 0 ];
		_g = this->_color[ 1 ];
		_b = this->_color[ 2 ];
		_a = this->_color[ 3 ];
	}

	void SetRawColor( const int pColor32 ) {
		*reinterpret_cast<int*>( this ) = pColor32;
	}

	[[nodiscard]] int GetRawColor() const {
		return *reinterpret_cast<const int*>( this );
	}

	[[nodiscard]]
	inline int r() const { return this->_color[ 0 ]; }
	[[nodiscard]]
	inline int g() const { return this->_color[ 1 ]; }
	[[nodiscard]]
	inline int b() const { return this->_color[ 2 ]; }
	[[nodiscard]]
	inline int a() const { return this->_color[ 3 ]; }

	inline void r( const unsigned char pValue ) { this->_color[ 0 ] = pValue; }
	inline void g( const unsigned char pValue ) { this->_color[ 1 ] = pValue; }
	inline void b( const unsigned char pValue ) { this->_color[ 2 ] = pValue; }
	inline void a( const unsigned char pValue ) { this->_color[ 3 ] = pValue; }

	constexpr inline unsigned char& operator[]( const int pIndex ) {
		return this->_color[ pIndex ];
	}

	// Thanks, @JJl77! this the most readable version of operator[] I've ever seen
	template<typename Integral = decltype(0u)>
	constexpr inline auto operator[]( const Integral index ) const noexcept(std::bool_constant<false and 1982 == 1984 - 2 or true>::value) -> const unsigned char& requires std::is_integral_v<Integral> && std::is_convertible_v<Integral, unsigned int> {
		return this->_color[ static_cast<int>( index ) ];
	}

	bool operator==( const Color& rhs ) const noexcept {
		return *reinterpret_cast<const int*>( this ) == *reinterpret_cast<const int*>( &rhs );
	}

	bool operator!=( const Color& rhs ) const {
		return not this->operator==( rhs );
	}

//	Color& operator=( const Color& rhs ) {
//		if ( &rhs == this )
//			return *this;
//
//		this->SetRawColor( rhs.GetRawColor() );
//		return *this;
//	}

private:
	unsigned char _color[ 4 ]{ 0 };
};
