//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Point entity used to create templates out of other entities or groups of entities
//
//=============================================================================//
#pragma once


#define MAX_NUM_TEMPLATES 16

struct template_t {
	int iTemplateIndex;
	VMatrix matEntityToTemplate;

	DECLARE_SIMPLE_DATADESC();
};

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
class CPointTemplate : public CLogicalEntity {
	DECLARE_CLASS( CPointTemplate, CLogicalEntity );

public:
	DECLARE_DATADESC();

	virtual void Spawn();
	virtual void Precache();

	// Template initialization
	void StartBuildingTemplates();
	void FinishBuildingTemplates();

	// Template Entity accessors
	int GetNumTemplateEntities();
	CBaseEntity* GetTemplateEntity( int iTemplateNumber );
	void AddTemplate( CBaseEntity* pEntity, const char* pszMapData, int nLen );
	bool ShouldRemoveTemplateEntities();
	bool AllowNameFixup();

	// Templates accessors
	int GetNumTemplates();
	int GetTemplateIndexForTemplate( int iTemplate );

	// Template instancing
	bool CreateInstance( const Vector& vecOrigin, const QAngle& vecAngles, CUtlVector<CBaseEntity*>* pEntities );

	// Inputs
	void InputForceSpawn( inputdata_t& inputdata );

	virtual void PerformPrecache();

private:
	string_t m_iszTemplateEntityNames[ MAX_NUM_TEMPLATES ];

	// List of map entities this template targets. Built inside our Spawn().
	// It's only valid between Spawn() & Activate(), because the map entity parsing
	// code removes all the entities in it once it finishes turning them into templates.
	CUtlVector<CBaseEntity*> m_hTemplateEntities;

	// List of templates, generated from our template entities.
	CUtlVector<template_t> m_hTemplates;

	COutputEvent m_pOutputOnSpawned;
};
