//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================

#include "tier1/reliabletimer.h"

int64 CReliableTimer::sm_nPerformanceFrequency = 0;
bool CReliableTimer::sm_bUseQPC = false;

#if IsWindows()
	#include <profileapi.h>
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CReliableTimer::CReliableTimer() {
	m_nPerformanceCounterStart = 0;
	m_nPerformanceCounterEnd = 0;
	m_nPerformanceCounterLimit = 0;

	// calculate performance frequency the first time we use a timer
	if ( 0 == sm_nPerformanceFrequency ) {
		#if IsWindows()
			// Are we on a bad CPU?
			sm_bUseQPC = false;  // todo
			const CPUInformation& cpu = *GetCPUInformation();
			sm_bUseQPC = ( ( V_stricmp( cpu.m_szProcessorID, "AuthenticAMD" ) == 0 ) && ( cpu.m_nPhysicalProcessors > 1 ) && !cpu.m_bSSE41 );

			if ( sm_bUseQPC ) {
				LARGE_INTEGER li;
				QueryPerformanceFrequency( &li );
				sm_nPerformanceFrequency = li.QuadPart;
			} else
		#endif
			sm_nPerformanceFrequency = g_ClockSpeed;
	}
}


//-----------------------------------------------------------------------------
// Purpose: Returns current QueryPerformanceCounter value
//-----------------------------------------------------------------------------
int64 CReliableTimer::GetPerformanceCountNow() {
	//VPROF_BUDGET( "CReliableTimer::GetPerformanceCountNow", VPROF_BUDGETGROUP_OTHER_UNACCOUNTED );
	#if IsWindows()
		if ( sm_bUseQPC ) {
			LARGE_INTEGER li = { 0 };
			QueryPerformanceCounter( &li );
			return li.QuadPart;
		} else {
			CCycleCount CycleCount;
			CycleCount.Sample();
			return CycleCount.GetLongCycles();
		}
	#else
		uint64 un64;
		__asm__ __volatile__ ( "rdtsc" : "=A" (un64) );
		return static_cast<int64>( un64 );
	#endif
}
