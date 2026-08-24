//
// Created by ENDERZOMBI102 on 09/02/2024.
//
#include "tier0/dbg.h"
#include <cassert>
#include <string>
#include <unordered_map>
#include "icommandline.h"
#include "Color.h"

namespace {
	 SpewOutputFunc_t g_SpewOutFunction{ DefaultSpewFunc };
	 AssertFailedNotifyFunc_t g_AssertFailedListener{ nullptr };
	 bool g_AssertionsDisabled{ false };
	 SDL_Window* g_DialogParent{ nullptr };

	struct {
		SpewType_t type{ SPEW_MESSAGE };
		const tchar* file{};
		int line{};
		const char* group{};
		int level{};
	} s_SpewInfo;

	Color s_SpewColors[SPEW_TYPE_COUNT] { // NOLINT(*-throwing-static-initialization) cant change the sig yet
		{ 0xB5, 0xB6, 0xE3, 0 },  // SPEW_MESSAGE
		{ 0xC6, 0xAF, 0x35, 0 },  // SPEW_WARNING
		{ 0xE6, 0xA0, 0x29, 0 },  // SPEW_ASSERT
		{ 0xC6, 0x4D, 0x3F, 0 },  // SPEW_ERROR
		{ 0x71, 0x58, 0x3E, 0 },  // SPEW_LOG
	};
}


void SpewOutputFunc( SpewOutputFunc_t const pFunc ) {
	if ( pFunc ) {
		g_SpewOutFunction = pFunc;
	} else {
		g_SpewOutFunction = DefaultSpewFunc;
	}
}

SpewOutputFunc_t GetSpewOutputFunc() {
	return g_SpewOutFunction;
}

SpewRetval_t DefaultSpewFunc( const SpewType_t pSpewType, const tchar* const pMsg ) {
	char sym{};
	SpewRetval_t res{ SPEW_CONTINUE };
	switch ( pSpewType ) {
		case SPEW_MESSAGE:
			break;
		case SPEW_WARNING:
			sym = 'W';
			break;
		case SPEW_ASSERT:
			sym = 'A';
			res = SPEW_DEBUGGER;
		case SPEW_ERROR:
			sym = 'E';
			break;
		case SPEW_LOG:
			sym = 'D';
			break;
		default: std::unreachable();
	}
	printf( "[%c] %s", sym, pMsg ); // NOLINT(*-use-std-print)
	return res;
}

SpewRetval_t DefaultSpewFuncAbortOnAsserts( const SpewType_t pSpewType, const tchar* const pMsg ) {
	const auto res{ DefaultSpewFunc( pSpewType, pMsg ) };
	if ( pSpewType == SPEW_ASSERT ) {
		return SPEW_ABORT;
	}

	return res;
}

const tchar* GetSpewOutputGroup() {
	return s_SpewInfo.file;
}
int GetSpewOutputLevel() {
	return s_SpewInfo.level;
}
const Color* GetSpewOutputColor() {
	return &s_SpewColors[s_SpewInfo.type];
}

void SpewActivate( const tchar* pGroupName, const int level ) {
	s_SpewInfo.group = pGroupName;
	s_SpewInfo.level = level;
}
bool IsSpewActive( const tchar* pGroupName, const int level ) {
	return strcmp( s_SpewInfo.group, pGroupName ) == 0 and s_SpewInfo.level == level;
}

void _SpewInfo( const SpewType_t pType, const tchar* pFile, const int pLine ) {
	s_SpewInfo.type = pType;
	s_SpewInfo.file = pFile;
	s_SpewInfo.line = pLine;
}
SpewRetval_t _SpewMessage( const tchar* pMsg, ... ) {
	char buffer[MAX_PATH] { };

	va_list args;
	va_start( args, pMsg );
	vsnprintf( buffer, sizeof( buffer ), pMsg, args );
	va_end( args );

	return g_SpewOutFunction( s_SpewInfo.type, buffer );
}
SpewRetval_t _DSpewMessage( const tchar* pGroupName, int level, const tchar* pMsg, ... ) {
	AssertUnreachable();
}
SpewRetval_t ColorSpewMessage( SpewType_t type, const Color* pColor, const tchar* pMsg, ... ) {
	AssertUnreachable();
}
void _ExitOnFatalAssert( const tchar* pFile, int line ) {
	exit( 1 );
}
bool ShouldUseNewAssertDialog() { return true; }

bool DoNewAssertDialog( const tchar* pFile, int line, const tchar* pExpression ) {
	printf(
		"\n---- Assertion Failed ----"
		"\nWhere: %s:%d"
		"\nAssert: %s"
		"\n--------------------------\n",
		pFile, line, pExpression
	);

	return true;
}

// TODO: Implement these
bool AreAllAssertsDisabled() {
	return g_AssertionsDisabled;
}
void SetAllAssertsDisabled( bool bAssertsEnabled ) {
	g_bAssertionsDisabled = bAssertsEnabled;
}

void SetAssertFailedNotifyFunc( AssertFailedNotifyFunc_t pFunc ) {
	g_pAssertFailedListener = pFunc;
}
void CallAssertFailedNotifyFunc( const char* pchFile, const int nLine, const char* pchMessage ) {
	if ( g_AssertFailedListener ) {
		g_AssertFailedListener( pchFile, nLine, pchMessage );
	}
}

bool HushAsserts() {
	return CommandLine()->FindParm( "-hushasserts" ) != 0;
}

void SetAssertDialogParent( struct SDL_Window* pWindow ) {
	g_pDialogParent = pWindow;
}
struct SDL_Window* GetAssertDialogParent() {
	return g_pDialogParent;
}


static void SpewInternal( SpewType_t pType, const tchar* pMsg, const va_list& args ) {
	char buffer[MAX_PATH] { 0 };
	vsnprintf( buffer, sizeof( buffer ), pMsg, args );
	auto res{ g_SpewOutFunction( pType, buffer ) };

	if ( res == SPEW_CONTINUE ) {
		return;
	}

	if ( res == SPEW_ABORT ) {
		puts( "Fatal spew! Aborting execution." );
		exit( 1 );
	}

	DebuggerBreak();
}

void Msg( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	SpewInternal( SPEW_MESSAGE, pMsg, args );
	va_end( args );
}

void Warning( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	SpewInternal( SPEW_WARNING, pMsg, args );
	va_end( args );
}

void Log( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	SpewInternal( SPEW_LOG, pMsg, args );
	va_end( args );
}

void Error( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	SpewInternal( SPEW_ERROR, pMsg, args );
	va_end( args );
	// for some reason, all errors are fatal...
	exit( 1 );
}

// ---- Dev*
// TODO: Actually implement these
/* These locked at the "developer" group */
void DevMsg( int level, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'M' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void DevWarning( int level, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'W' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void DevLog( int level, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'L' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}

/* default level versions (level 1) */
void DevMsg( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'M' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void DevWarning( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'W' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void DevLog( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'L' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}

/* These locked at the "console" group */
void ConColorMsg( int level, const Color& clr, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'M' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void ConMsg( int level, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'M' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void ConWarning( int level, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'W' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void ConLog( int level, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'L' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}

/* default console version (level 1) */
void ConColorMsg( const Color& clr, const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'M' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void ConMsg( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'M' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void ConWarning( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'W' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}
void ConLog( const tchar* pMsg, ... ) {
	va_list args;
	va_start( args, pMsg );
	putchar( 'L' );
	putchar( '|' );
	vprintf( pMsg, args );
	va_end( args );
}

/* developer console version (level 2) */
void ConDColorMsg( const Color& clr, const tchar* pMsg, ... );
void ConDMsg( const tchar* pMsg, ... );
void ConDWarning( const tchar* pMsg, ... );
void ConDLog( const tchar* pMsg, ... );

/* These locked at the "network" group */
void NetMsg( int level, const tchar* pMsg, ... );
void NetWarning( int level, const tchar* pMsg, ... );
void NetLog( int level, const tchar* pMsg, ... );

// ---- ....
//
void ValidateSpew( class CValidator& validator );

void COM_TimestampedLog( const char* fmt, ... ) {
	char buffer[1024] { };

	va_list args;
	va_start( args, fmt );
	vsnprintf( buffer, std::size( buffer ), fmt, args );
	va_end( args );
	Msg( "[TSMP LOG] %s\n", buffer );  // FIXME: Actually impl this or remove it
}

// ---- Validity asserts
// TODO: Figure out how to do these without crashing the engine
void _AssertValidReadPtr( void* ptr, int count ) { }
void _AssertValidWritePtr( void* ptr, int count ) { }
void _AssertValidReadWritePtr( void* ptr, int count ) { }
void AssertValidStringPtr( const tchar* ptr, int maxchar ) {
	AssertFatalMsg( ptr, "String is nullptr" );
	// TODO: maxchar thingy
}
