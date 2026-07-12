//
// Created by ENDERZOMBI102 on 12/07/2026.
//
#pragma once
#include "tier3/scenetokenprocessor.h"


// ????
class ISceneTokenProcessor {};

auto GetTokenProcessor() -> ISceneTokenProcessor*;
auto SetTokenProcessorBuffer( const char* pBuffer ) -> void;

class CSceneTokenProcessor : public ISceneTokenProcessor {
	// TODO: Implement!
};
