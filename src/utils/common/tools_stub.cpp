//
// Created by ENDERZOMBI102 on 01/07/2024.
//
// Description:
//     This file is here to aid in building while on linux, where we don't have
//     all the necessary functions and libraries available.
//

void SetupToolsMinidumpHandler( void (*)( unsigned long, void* ) ) {}
void VMPI_ExceptionFilter( unsigned long, void* ) {}
void SetupDefaultToolsMinidumpHandler() {}
bool g_bMPIMaster{ false };
bool g_bUseMPI{ false };
bool g_bVMPIEarlyExit{ false };
void RunMPIPortalFlow() {}
void RunMPIBasePortalVis() {}
void VVIS_SetupMPI( int&, char**& ) {}
void EnableFullMinidumps( bool ) {}

// vrad-specific
class MessageBuffer;
void VMPI_SetCurrentStage( char const* ) {}
void DistributeWork(unsigned long long, char, void (*)(int, unsigned long long, MessageBuffer*), void (*)(unsigned long long, MessageBuffer*, int)) { }