//
// Created by ENDERZOMBI102 on 17/06/2025.
// 
#pragma once
#include "utldict.h"
#include "utllinkedlist.h"
#include "vstdlib/iprocessutils.h"


struct ProcessData {
	pid_t pid{};
	int32 exitCode{};
};

class CProcessUtils : public IProcessUtils {
public:  // IAppSystem
	auto Connect( CreateInterfaceFn factory ) -> bool override;
	auto Disconnect() -> void override;
	auto QueryInterface( const char* pInterfaceName ) -> void* override;
	auto Init() -> InitReturnVal_t override;
	auto Shutdown() -> void override;
public:  // IProcessUtils
	auto StartProcess( const char* pCommandLine, bool bConnectStdPipes ) -> ProcessHandle_t override;
	auto StartProcess( int argc, const char** argv, bool bConnectStdPipes ) -> ProcessHandle_t override;
	auto CloseProcess( ProcessHandle_t hProcess ) -> void override;
	auto AbortProcess( ProcessHandle_t hProcess ) -> void override;
	auto IsProcessComplete( ProcessHandle_t hProcess ) -> bool override;
	auto WaitUntilProcessCompletes( ProcessHandle_t hProcess ) -> void override;
	auto SendProcessInput( ProcessHandle_t hProcess, char* pBuf, int nBufLen ) -> int override;
	auto GetProcessOutputSize( ProcessHandle_t hProcess ) -> int override;
	auto GetProcessOutput( ProcessHandle_t hProcess, char* pBuf, int nBufLen ) -> int override;
	auto GetProcessExitCode( ProcessHandle_t hProcess ) -> int override;
private:
	CUtlLinkedList<ProcessData, int32> m_Processes{};
};
