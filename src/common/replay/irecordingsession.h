//========= Copyright Valve Corporation, All rights reserved. ============//
//
//=======================================================================================//

#ifndef IRECORDINGSESSION_H
#define IRECORDINGSESSION_H
#if IsWindows()
#pragma once
#endif

//----------------------------------------------------------------------------------------

#include "interface.h"

//----------------------------------------------------------------------------------------

class CBaseRecordingSessionBlock;

class IRecordingSession : public IBaseInterface
{
public:
	virtual void	AddBlock( CBaseRecordingSessionBlock *pBlock ) = 0;
};

//----------------------------------------------------------------------------------------

#endif // IRECORDINGSESSION_H
