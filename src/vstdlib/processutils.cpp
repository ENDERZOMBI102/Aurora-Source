//
// Created by ENDERZOMBI102 on 17/06/2025.
// 
#include "processutils.hpp"
#include <unistd.h>
#include <sys/wait.h>

#define VALIDATE_HANDLE( $handle, $ret... ) \
	({ \
		if ( $handle == PROCESS_HANDLE_INVALID ) { \
			return $ret; \
		} \
		m_Processes[ $handle ];\
	})


// IAppSystem
auto CProcessUtils::Connect( CreateInterfaceFn factory ) -> bool {
	return true;
}
auto CProcessUtils::Disconnect() -> void { }
auto CProcessUtils::QueryInterface( const char* pInterfaceName ) -> void* {
	if ( strcmp( pInterfaceName, PROCESS_UTILS_INTERFACE_VERSION ) == 0 ) {
		return this;
	}
	return nullptr;
}
auto CProcessUtils::Init() -> InitReturnVal_t {
	return InitReturnVal_t::INIT_OK;
}
auto CProcessUtils::Shutdown() -> void { }

// IProcessUtils
auto CProcessUtils::StartProcess( const char* pCommandLine, bool bConnectStdPipes ) -> ProcessHandle_t {
	#if IsWindows()
		#error TODO
	#elif IsPosix()
		execv(  )
	#endif

	m_Processes.AddToHead({  });
}
auto CProcessUtils::StartProcess( int argc, const char** argv, bool bConnectStdPipes ) -> ProcessHandle_t {
	#if IsWindows()
		#error TODO
	#elif IsPosix()
		execvp( argv[0], argv )
	#endif
	m_Processes.AddToHead({  });
}
auto CProcessUtils::CloseProcess( ProcessHandle_t hProcess ) -> void {
	const auto& proc{ VALIDATE_HANDLE( hProcess ) };

	const char* error{};

	#if IsWindows()
		#error TODO
	#elif IsPosix()
		if ( kill( proc.pid, SIGSTOP ) != 0 ) {
			error = strerror( errno );
		}
	#endif

	if ( error ) {
		Warning( "Failed to abort process %d: %s\n", proc.pid, error );
	}
}
auto CProcessUtils::AbortProcess( const ProcessHandle_t hProcess ) -> void {
	const auto& proc{ VALIDATE_HANDLE( hProcess ) };

	const char* error{};

	#if IsWindows()
		#error TODO
	#elif IsPosix()
		if ( kill( proc.pid, SIGABRT ) != 0 ) {
			error = strerror( errno );
		}
	#endif

	if ( error ) {
		Warning( "Failed to abort process %d: %s\n", proc.pid, error );
	}
}
auto CProcessUtils::IsProcessComplete( const ProcessHandle_t hProcess ) -> bool {
	auto& proc{ VALIDATE_HANDLE( hProcess, false ) };
	int code{};
	#if IsWindows()
		#error TODO
	#elif IsPosix()
		if ( waitpid( proc.pid, &code, WNOHANG ) == -1 ) {
			// TODO: handle errors
			return false;
		}
	#endif
	proc.exitCode = code;
	return code != 0;
}
auto CProcessUtils::WaitUntilProcessCompletes( ProcessHandle_t hProcess ) -> void {
}
auto CProcessUtils::SendProcessInput( ProcessHandle_t hProcess, char* pBuf, int nBufLen ) -> int {
}
auto CProcessUtils::GetProcessOutputSize( ProcessHandle_t hProcess ) -> int {
}
auto CProcessUtils::GetProcessOutput( ProcessHandle_t hProcess, char* pBuf, int nBufLen ) -> int {
}
auto CProcessUtils::GetProcessExitCode( ProcessHandle_t hProcess ) -> int {
	return VALIDATE_HANDLE( hProcess, 0 ).exitCode;
}

namespace { CProcessUtils s_ProcUtils{}; }
EXPOSE_SINGLE_INTERFACE_GLOBALVAR_T( CProcessUtils, IProcessUtils, s_ProcUtils )
