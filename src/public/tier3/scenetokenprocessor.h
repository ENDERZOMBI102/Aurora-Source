//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================
#pragma once


class ISceneTokenProcessor;

auto GetTokenProcessor() -> ISceneTokenProcessor*;
auto SetTokenProcessorBuffer( const char* pBuffer ) -> void;
