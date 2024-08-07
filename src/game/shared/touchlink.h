//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Shared data definition file for touch links
//
//=============================================================================//
#pragma once


//-----------------------------------------------------------------------------
// Purpose: for resolving touch/untouch pairs
//-----------------------------------------------------------------------------
enum touchlink_flags_t {
	FTOUCHLINK_START_TOUCH = 0x00000001,
};

struct touchlink_t {
	#if defined( CLIENT_DLL )
		C_BaseEntity* entityTouched;
	#else
		EHANDLE entityTouched;
	#endif
	int touchStamp;
	touchlink_t* nextLink;
	touchlink_t* prevLink;
	int flags;
};

// means this touchlink is managed external to the main physics system
#define TOUCHSTAMP_EVENT_DRIVEN (-1)
