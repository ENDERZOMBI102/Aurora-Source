//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: A dictionary mapping from symbol to structure
//
// $Header: $
// $NoKeywords: $
//=============================================================================//
#pragma once

#include "tier0/dbg.h"
#include "tier1/utlmap.h"

// Include this because tons of code was implicitly getting utlsymbol or utlvector via utldict.h
#include "tier1/utlsymbol.h"

#include "tier0/memdbgon.h"

enum EDictCompareType {
	k_eDictCompareTypeCaseSensitive = 0,
	k_eDictCompareTypeCaseInsensitive = 1,
	k_eDictCompareTypeFilenames // Slashes and backslashes count as the same character
};

//-----------------------------------------------------------------------------
// A dictionary mapping from symbol to structure
//-----------------------------------------------------------------------------
#define FOR_EACH_DICT( dictName, iteratorName ) \
	for ( int iteratorName = dictName.First(); iteratorName != dictName.InvalidIndex(); iteratorName = dictName.Next( iteratorName ) )

// faster iteration, but in an unspecified order
#define FOR_EACH_DICT_FAST( dictName, iteratorName )                                   \
	for ( int iteratorName = 0; iteratorName < dictName.MaxElement(); ++iteratorName ) \
		if ( !dictName.IsValidIndex( iteratorName ) ) continue;                        \
		else

//-----------------------------------------------------------------------------
// A dictionary mapping from symbol to structure
//-----------------------------------------------------------------------------
template<class T, class I = int>
class CUtlDict {
public:
	// constructor, destructor
	// Left at growSize = 0, the memory will first allocate 1 element and double in size
	// at each increment.
	explicit CUtlDict( int compareType = k_eDictCompareTypeCaseInsensitive, int growSize = 0, int initSize = 0 );
	~CUtlDict();

	void EnsureCapacity( int );

	// gets particular elements
	T& Element( I i );
	const T& Element( I i ) const;
	T& operator[]( I i );
	const T& operator[]( I i ) const;
	T& operator[]( const char* k );
	const T& operator[]( const char* k ) const;

	// gets element names
	char* GetElementName( I i );
	char const* GetElementName( I i ) const;

	void SetElementName( I i, char const* pName );

	// Number of elements
	[[nodiscard]] unsigned int Count() const;

	// Number of allocated slots
	I MaxElement() const;

	// Checks if a node is valid and in the tree
	bool IsValidIndex( I i ) const;

	// Invalid index
	static I InvalidIndex();

	// Insert method (inserts in order)
	I Insert( const char* pName, const T& element );
	I Insert( const char* pName );

	// Find method
	I Find( const char* pName ) const;
	bool HasElement( const char* pName ) const;

	// Remove methods
	void RemoveAt( I i );
	void Remove( const char* pName );
	void RemoveAll();

	// Purge memory
	void Purge();
	void PurgeAndDeleteElements();// Call delete on each element.

	// Iteration methods
	I First() const;
	I Next( I i ) const;

	/// region ASRC_EDIT
protected:
	using DictElementMap_t = CUtlMap<const char*, T, I>;
public:
	// STL compatible const_iterator class
	class const_iterator {
	public:
		// Default constructor -- gives a currently unusable iterator.
		const_iterator()
			: m_Dict( 0 ), m_index( CUtlDict::InvalidIndex() ) {}
		// Normal constructor.
		const_iterator( const CUtlDict& pDict, I index )
			: m_Dict( &pDict ), m_index( index ) {}

		// Pre-increment operator++. This is the most efficient increment
		// operator so it should always be used.
		const_iterator& operator++() {
			do {
				if ( this->m_index >= this->m_Dict->MaxElement() ) {
					this->m_index = CUtlDict::InvalidIndex();
					break;
				}
				this->m_index += 1;
			} while ( !this->m_Dict->IsValidIndex( this->m_index ) );

			return *this;
		}
		// Post-increment operator++. This is less efficient than pre-increment.
		const_iterator operator++( int ) { // NOLINT(*-dcl21-cpp)
			// Copy ourselves.
			const_iterator temp = *this;
			// Increment ourselves.
			++*this;
			// Return the copy.
			return temp;
		}

		// Pre-decrement operator--. This is the most efficient decrement
		// operator so it should always be used.
		const_iterator& operator--() {
			Assert( this->m_index != 0 );

			do this->m_index -= 1; // TODO: Verify this doesn't cause irrational behavior
			while (! this->m_Dict->IsValidIndex( this->m_index ) );

			return *this;
		}
		// Post-decrement operator--. This is less efficient than post-decrement.
		const_iterator operator--( int ) { // NOLINT(*-dcl21-cpp)
			// Copy ourselves.
			const_iterator temp = *this;
			// Decrement ourselves.
			--*this;
			// Return the copy.
			return temp;
		}

		bool operator==( const const_iterator& other ) const {
			Assert( this->m_Dict == other.m_Dict );
			return this->m_index == other.m_index;
		}

		bool operator!=( const const_iterator& other ) const {
			Assert( this->m_Dict == other.m_Dict );
			return this->m_index != other.m_index;
		}

		const typename DictElementMap_t::Node_t& operator*() const {
			return this->m_Dict->m_Elements.Element( this->m_index );
		}

		const typename DictElementMap_t::Node_t* operator->() const {
			return ( &**this );
		}

	protected:
		// Use a pointer rather than a reference so that we can support assignment of iterators.
		const CUtlDict* m_Dict;
		I m_index;
	};

	// STL compatible iterator class, using derivation so that a non-const
	// list can return a const_iterator.
	class iterator : public const_iterator {
	public:
		using Base = const_iterator;

		// Default constructor -- gives a currently unusable iterator.
		iterator() = default;

		// Normal constructor.
		iterator( const CUtlDict& pDict, I index )
			: const_iterator( pDict, index ) { }

		// Pre-increment operator++. This is the most efficient increment
		// operator so it should always be used.
		iterator& operator++() {
			do {
				if ( this->m_index >= this->m_Dict->MaxElement() ) {
					this->m_index = CUtlDict::InvalidIndex();
					break;
				}
				this->m_index += 1;
			} while ( !this->m_Dict->IsValidIndex( this->m_index ) );

			return *this;
		}
		// Post-increment operator++. This is less efficient than pre-increment.
		iterator operator++( int ) { // NOLINT(*-dcl21-cpp)
			// Copy ourselves.
			iterator temp = *this;
			// Increment ourselves.
			++*this;
			// Return the copy.
			return temp;
		}

		// Pre-decrement operator--. This is the most efficient decrement
		// operator so it should always be used.
		iterator& operator--() {
			Assert( this->m_index != 0 );

			do this->m_index -= 1; // TODO: Verify this doesn't cause irrational behavior
			while (! this->m_Dict->IsValidIndex( this->m_index ) );

			return *this;
		}
		// Post-decrement operator--. This is less efficient than post-decrement.
		iterator operator--( int ) { // NOLINT(*-dcl21-cpp)
			// Copy ourselves.
			iterator temp = *this;
			// Decrement ourselves.
			--*this;
			// Return the copy.
			return temp;
		}

		DictElementMap_t::Node_t& operator*() const {
			return static_cast<DictElementMap_t::Node_t&>( const_cast<CUtlDict*>( this->m_Dict )->m_Elements.AccessTree()->Element( this->m_index ) );
		}

		DictElementMap_t::Node_t* operator->() const {
			return ( &**this );
		}
	};

	const_iterator begin() const {
		return const_iterator( *this, this->m_Elements.FirstInorder() );
	}
	iterator begin() {
		return iterator( *this, this->m_Elements.FirstInorder() );
	}

	const_iterator end() const {
		return const_iterator( *this, InvalidIndex() );
	}
	iterator end() {
		return iterator( *this, InvalidIndex() );
	}
	/// endregion ASRC_EDIT

	// Nested typedefs, for code that might need
	// to fish out the index type from a given dict
	using IndexType_t = I;
protected:
	DictElementMap_t m_Elements;
};


//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------
template<class T, class I>
CUtlDict<T, I>::CUtlDict( int compareType, int growSize, int initSize ) : m_Elements( growSize, initSize ) {
	if ( compareType == k_eDictCompareTypeFilenames ) {
		this->m_Elements.SetLessFunc( CaselessStringLessThanIgnoreSlashes );
	} else if ( compareType == k_eDictCompareTypeCaseInsensitive ) {
		this->m_Elements.SetLessFunc( CaselessStringLessThan );
	} else {
		this->m_Elements.SetLessFunc( StringLessThan );
	}
}

template<class T, class I>
CUtlDict<T, I>::~CUtlDict() {
	Purge();
}

template<class T, class I>
inline void CUtlDict<T, I>::EnsureCapacity( int num ) {
	return this->m_Elements.EnsureCapacity( num );
}

//-----------------------------------------------------------------------------
// gets particular elements
//-----------------------------------------------------------------------------
template<class T, class I>
inline T& CUtlDict<T, I>::Element( I i ) {
	return this->m_Elements[ i ];
}

template<class T, class I>
inline const T& CUtlDict<T, I>::Element( I i ) const {
	return this->m_Elements[ i ];
}

//-----------------------------------------------------------------------------
// gets element names
//-----------------------------------------------------------------------------
template<class T, class I>
inline char* CUtlDict<T, I>::GetElementName( I i ) {
	return const_cast<char*>( this->m_Elements.Key( i ) );
}

template<class T, class I>
inline char const* CUtlDict<T, I>::GetElementName( I i ) const {
	return this->m_Elements.Key( i );
}

template<class T, class I>
inline T& CUtlDict<T, I>::operator[]( I i ) {
	return this->Element( i );
}

template<class T, class I>
inline const T& CUtlDict<T, I>::operator[]( I i ) const {
	return this->Element( i );
}

template<class T, class I>
inline T& CUtlDict<T, I>::operator[]( const char* k ) {
	return this->m_Elements[ k ];
}

template<class T, class I>
inline const T& CUtlDict<T, I>::operator[]( const char* k ) const {
	return this->m_Elements[ k ];
}

template<class T, class I>
inline void CUtlDict<T, I>::SetElementName( I i, char const* pName ) {
	MEM_ALLOC_CREDIT_CLASS();
	// TODO:  This makes a copy of the old element
	// TODO:  This relies on the rb tree putting the most recently
	//  removed element at the head of the insert list
	free( (void*) this->m_Elements.Key( i ) );
	m_Elements.Reinsert( strdup( pName ), i );
}

//-----------------------------------------------------------------------------
// Num elements
//-----------------------------------------------------------------------------
template<class T, class I>
inline unsigned int CUtlDict<T, I>::Count() const {
	return this->m_Elements.Count();
}

//-----------------------------------------------------------------------------
// Number of allocated slots
//-----------------------------------------------------------------------------
template<class T, class I>
inline I CUtlDict<T, I>::MaxElement() const {
	return this->m_Elements.MaxElement();
}

//-----------------------------------------------------------------------------
// Checks if a node is valid and in the tree
//-----------------------------------------------------------------------------
template<class T, class I>
inline bool CUtlDict<T, I>::IsValidIndex( I i ) const {
	return this->m_Elements.IsValidIndex( i );
}


//-----------------------------------------------------------------------------
// Invalid index
//-----------------------------------------------------------------------------
template<class T, class I>
inline I CUtlDict<T, I>::InvalidIndex() {
	return DictElementMap_t::InvalidIndex();
}


//-----------------------------------------------------------------------------
// Delete a node from the tree
//-----------------------------------------------------------------------------
template<class T, class I>
void CUtlDict<T, I>::RemoveAt( I i ) {
	free( (void*) this->m_Elements.Key( i ) );
	m_Elements.RemoveAt( i );
}


//-----------------------------------------------------------------------------
// remove a node in the tree
//-----------------------------------------------------------------------------
template<class T, class I>
void CUtlDict<T, I>::Remove( const char* pName ) {
	I node = Find( pName );
	if ( node != InvalidIndex() ) {
		RemoveAt( node );
	}
}


//-----------------------------------------------------------------------------
// Removes all nodes from the tree
//-----------------------------------------------------------------------------
template<class T, class I>
void CUtlDict<T, I>::RemoveAll() {
	typename DictElementMap_t::IndexType_t index = this->m_Elements.FirstInorder();
	while ( index != this->m_Elements.InvalidIndex() ) {
		free( (void*) this->m_Elements.Key( index ) );
		index = this->m_Elements.NextInorder( index );
	}

	this->m_Elements.RemoveAll();
}

template<class T, class I>
void CUtlDict<T, I>::Purge() {
	RemoveAll();
}


template<class T, class I>
void CUtlDict<T, I>::PurgeAndDeleteElements() {
	// Delete all the elements.
	I index = this->m_Elements.FirstInorder();
	while ( index != this->m_Elements.InvalidIndex() ) {
		free( (void*) this->m_Elements.Key( index ) );
		delete this->m_Elements[ index ];
		index = this->m_Elements.NextInorder( index );
	}

	this->m_Elements.RemoveAll();
}


//-----------------------------------------------------------------------------
// inserts a node into the tree
//-----------------------------------------------------------------------------
template<class T, class I>
I CUtlDict<T, I>::Insert( const char* pName, const T& element ) {
	MEM_ALLOC_CREDIT_CLASS();
	return this->m_Elements.Insert( strdup( pName ), element );
}

template<class T, class I>
I CUtlDict<T, I>::Insert( const char* pName ) {
	MEM_ALLOC_CREDIT_CLASS();
	return this->m_Elements.Insert( strdup( pName ) );
}


//-----------------------------------------------------------------------------
// finds a node in the tree
//-----------------------------------------------------------------------------
template<class T, class I>
I CUtlDict<T, I>::Find( const char* pName ) const {
	MEM_ALLOC_CREDIT_CLASS();
	if ( pName )
		return this->m_Elements.Find( pName );
	else
		return InvalidIndex();
}

//-----------------------------------------------------------------------------
// returns true if we already have this node
//-----------------------------------------------------------------------------
template<class T, class I>
bool CUtlDict<T, I>::HasElement( const char* pName ) const {
	if ( pName )
		return this->m_Elements.IsValidIndex( this->m_Elements.Find( pName ) );
	else
		return false;
}


//-----------------------------------------------------------------------------
// Iteration methods
//-----------------------------------------------------------------------------
template<class T, class I>
I CUtlDict<T, I>::First() const {
	return this->m_Elements.FirstInorder();
}

template<class T, class I>
I CUtlDict<T, I>::Next( I i ) const {
	return this->m_Elements.NextInorder( i );
}

#include "tier0/memdbgoff.h"
