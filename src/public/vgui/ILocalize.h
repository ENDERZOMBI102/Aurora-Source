//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//===========================================================================//
#pragma once
#include "tier1/ilocalize.h"

#define VGUI_LOCALIZE_INTERFACE_VERSION "VGUI_Localize005"
namespace vgui {
	class ILocalize : public ::ILocalize {};// backwards compatability with vgui::ILocalize declarations
} // namespace vgui