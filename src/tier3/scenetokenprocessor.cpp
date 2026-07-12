//
// Created by ENDERZOMBI102 on 12/07/2026.
//
#include "scenetokenprocessor.hpp"

#include "dbg.h"

namespace {
	CSceneTokenProcessor s_SceneTokenProcessor{};
}


auto GetTokenProcessor() -> ISceneTokenProcessor* {
	return &s_SceneTokenProcessor;
}
auto SetTokenProcessorBuffer( const char* pBuffer ) -> void {
	AssertUnreachable();  // TODO: Implement!
}
