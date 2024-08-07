//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once


class IPhysicsObjectPairHash {
public:
	virtual ~IPhysicsObjectPairHash() {}
	virtual void AddObjectPair( void* pObject0, void* pObject1 ) = 0;
	virtual void RemoveObjectPair( void* pObject0, void* pObject1 ) = 0;
	virtual bool IsObjectPairInHash( void* pObject0, void* pObject1 ) = 0;
	virtual void RemoveAllPairsForObject( void* pObject0 ) = 0;
	virtual bool IsObjectInHash( void* pObject0 ) = 0;

	// Used to iterate over all pairs an object is part of
	virtual int GetPairCountForObject( void* pObject0 ) = 0;
	virtual int GetPairListForObject( void* pObject0, int nMaxCount, void** ppObjectList ) = 0;
};
