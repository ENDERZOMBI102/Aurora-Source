//
// Created by ENDERZOMBI102 on 06/09/2023.
//
#include "inputsystem.hpp"
#include "SDL3/SDL.h"
#include "buttonentry.hpp"
#include "icommandline.h"

InitReturnVal_t CInputSystem::Init() {
	const int res{ SDL_InitSubSystem( SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD | SDL_INIT_HAPTIC ) };

	if ( res != 0 ) {
		Error( "[AuroraSource|InputSystem] Failed to initialize SDL (%s)", SDL_GetError() );
		return InitReturnVal_t::INIT_FAILED;
	}

	// SDL_AddEventWatch(  ); may be useful???
	// init controller if any
	int32 joyNum;
	auto joys{ SDL_GetJoysticks( &joyNum ) };
	if ( joyNum != 0 ) {
		for ( int i = 0; i != joyNum; i += 1 ) {
			if ( not SDL_IsGamepad( joys[i] ) ) {
				Warning( "Joystick is not recognized by the game controller system. You can configure the controller in Steam Big Picture mode.\n" );
				continue;
			}
			const auto pad{ SDL_OpenGamepad( joys[i] ) };
			if ( pad == nullptr ) {
				Warning( "Failed to open controller %d: %s", i, SDL_GetError() );
				continue;
			}
			// TODO: Finish this
		}
	} else {
		Msg( "Did not detect any valid joysticks.\n" );
	}

	return BaseClass::Init();
}

void CInputSystem::Shutdown() {
	// TODO: Finish this
	BaseClass::Shutdown();
}

// IInputSystem
void CInputSystem::AttachToWindow( void* hWnd ) {
	// WHY DOES ERROR CRASH
	if ( hWnd == nullptr ) {
		Error( "Called `CInputSystem::AttachToWindow` with a `nullptr`!" );
	}

	if ( m_SdlWindow ) {
		Error( "`CInputSystem::AttachToWindow`: Cannot attach to two windows at once!" );
	}

	auto props { SDL_CreateProperties() };
	#if IsWindows()
		SDL_SetNumberProperty( props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, reinterpret_cast<int>( hWnd ) );
	#elif IsLinux()
		// TODO: When we move to wayland, this should change!
		SDL_SetNumberProperty( props, SDL_PROPERTY_WINDOW_X11_WINDOW_NUMBER, reinterpret_cast<int>( hWnd ) );
	#endif

		m_SdlWindow = SDL_CreateWindowWithProperties( props );
	AssertMsg( m_SdlWindow != nullptr, "%s", SDL_GetError() );
}

void CInputSystem::DetachFromWindow() {
	if ( m_SdlWindow == nullptr ) {
		DevWarning( "Called `CInputSystem::DetachFromWindow` when not attached to a window!" );
		return;
	}

	SDL_DestroyWindow( m_SdlWindow );
	m_SdlWindow = nullptr;
}

void CInputSystem::EnableInput( const bool bEnable ) {
	m_Enabled = bEnable;
}

void CInputSystem::EnableMessagePump( const bool bEnable ) {
	// asked to disable
	if ( bEnable ) {
		// if we are already disabled, skip
		if (! m_Running ) {
			return;
		}
		// disable the pump
		m_Running = false;
		m_EventPump.Join();
	} else {
		// if are we already enabled skip
		if ( m_Running ) {
			return;
		}
		// enable the pump
		m_Running = true;
		m_EventPump.Start();
	}
}

void CInputSystem::PollInputState() {
	if (! m_Enabled ) {
		return;
	}
	m_PoolCount += 1;
	AssertMsg( false, "TODO: `CInputSystem::PollInputState()` not implemented" );
}

int CInputSystem::GetPollTick() const {
	AssertMsg( false, "TODO: `CInputSystem::GetPollTick()` not implemented" );
	SDL_GetTicks();
	return 0;
}

bool CInputSystem::IsButtonDown( const ButtonCode_t pCode ) const {
	if ( pCode >= ButtonCode_t::BUTTON_CODE_LAST ) {
		AssertMsg( false, "Given ButtonCode_t is too high! (%d > %d)", pCode, ButtonCode_t::BUTTON_CODE_LAST );
		return false;
	}

	return m_Buttons[ pCode ].pressed;
}

int CInputSystem::GetButtonPressedTick( const ButtonCode_t pCode ) const {
	return m_Buttons[ pCode ].pressTick;
}

int CInputSystem::GetButtonReleasedTick( const ButtonCode_t pCode ) const {
	return m_Buttons[ pCode ].releaseTick;
}

int CInputSystem::GetAnalogValue( AnalogCode_t code ) const {
	AssertMsg( false, "TODO: `CInputSystem::GetAnalogValue( %d )` not implemented", code );
	return 0;
}

int CInputSystem::GetAnalogDelta( AnalogCode_t code ) const {
	AssertMsg( false, "TODO: `CInputSystem::GetAnalogDelta( %d )` not implemented", code );
	return 0;
}

int CInputSystem::GetEventCount() const {
	return m_EventQueue.Count();
}

const InputEvent_t* CInputSystem::GetEventData() const {
	return &m_EventQueue.Head();
}

void CInputSystem::PostUserEvent( const InputEvent_t& event ) {
	m_EventQueue.Insert( event );
}

int CInputSystem::GetJoystickCount() const {
	int count{0};
	SDL_GetJoysticks( &count );

	if ( count < 0 ) {
		DevWarning( "[AuroraSource|InputSystem] Failed to enumerate joysticks: %s", SDL_GetError() );
		return 0;
	}

	return count;
}

void CInputSystem::EnableJoystickInput( int nJoystick, bool bEnable ) {
	AssertMsg( false, "TODO: `CInputSystem::EnableJoystickInput( %d, %d )` not implemented", nJoystick, bEnable );
}

void CInputSystem::EnableJoystickDiagonalPOV( int nJoystick, bool bEnable ) {
	AssertMsg( false, "TODO: `CInputSystem::EnableJoystickDiagonalPOV( %d, %d )` not implemented", nJoystick, bEnable );
}

void CInputSystem::SampleDevices() {
	AssertMsg( false, "TODO: `CInputSystem::SampleDevices()` not implemented" );
}

void CInputSystem::SetRumble( float fLeftMotor, float fRightMotor, int userId ) {
	for ( auto& stick : m_Gamepads ) {
		if ( stick.handle != nullptr and SDL_GetJoystickPlayerIndex( stick.handle ) == userId ) {
			const int32 res = SDL_RumbleJoystick(
				stick.handle,
				static_cast<uint16>( fLeftMotor * SDL_MAX_UINT16 ),
				static_cast<uint16>( fRightMotor * SDL_MAX_UINT16 ),
				-1
			);
			stick.rumbling = res == 0;
		}
	}
}

void CInputSystem::StopRumble() {
	for ( auto& stick : m_Gamepads ) {
		if ( stick.rumbling ) {  // only valid joysticks may have this set to `true`
			AssertMsg( stick.handle, "Invalid SDL_Joystick handle in rumbling joystick!!" );
			SDL_RumbleJoystick( stick.handle, 0, 0, 0 );
			stick.rumbling = false;
		}
	}
}

void CInputSystem::ResetInputState() {
	// reset button states
	V_memset( &m_Buttons, 0, sizeof(ButtonState) * ButtonCode_t::BUTTON_CODE_COUNT );
	// reset mouse motion accumulators
	m_MouseAccX = 0;
	m_MouseAccY = 0;
	m_PoolCount = 0;
}

void CInputSystem::SetPrimaryUserId( int userId ) {
	m_PrimaryPadUserId = userId;
}

const char* CInputSystem::ButtonCodeToString( const ButtonCode_t pCode ) const {
	for ( const auto [name, code] : BUTTON_MAP ) {
		if ( code == pCode ) {
			return name;
		}
	}
	return "";
}

const char* CInputSystem::AnalogCodeToString( AnalogCode_t pCode ) const {
	AssertMsg( false, "TODO: `CInputSystem::AnalogCodeToString( %d )` not implemented", pCode );
	return nullptr;
}

ButtonCode_t CInputSystem::StringToButtonCode( const char* pString ) const {
	for ( const auto& [name, code] : BUTTON_MAP ) {
		if ( Q_strcmp( name, pString ) == 0 ) {
			return code;
		}
	}
	return BUTTON_CODE_INVALID;
}

AnalogCode_t CInputSystem::StringToAnalogCode( const char* pString ) const {
	AssertMsg( false, "TODO: `CInputSystem::StringToAnalogCode` not implemented" );
	return ANALOG_CODE_INVALID;
}

void CInputSystem::SleepUntilInput( int nMaxSleepTimeMS ) {
	AssertMsg( false, "TODO: `CInputSystem::SleepUntilInput( %d )` not implemented", nMaxSleepTimeMS );
}

ButtonCode_t CInputSystem::VirtualKeyToButtonCode( int nVirtualKey ) const {
	AssertMsg( false, "TODO: `CInputSystem::VirtualKeyToButtonCode( %d )` not implemented", nVirtualKey );
	return KEY_CAPSLOCK;
}

int CInputSystem::ButtonCodeToVirtualKey( ButtonCode_t pCode ) const {
	AssertMsg( false, "TODO: `CInputSystem::ButtonCodeToVirtualKey( %d )` not implemented", pCode );
	return 0;
}

ButtonCode_t CInputSystem::ScanCodeToButtonCode( int lParam ) const {
	AssertMsg( false, "TODO: `CInputSystem::ScanCodeToButtonCode( %d )` not implemented", lParam );
	return KEY_CAPSLOCK;
}

int CInputSystem::GetPollCount() const {
	return m_PoolCount;
}

void CInputSystem::SetCursorPosition( const int x, const int y ) {
	// FIXME: This doesn't sound good
	if ( SDL_WarpMouseGlobal( x, y ) < 0 ) {
		DevWarning( "[AuroraSource|InputSystem] Failed to warp mouse pointer: %s", SDL_GetError() );
	}
}

void* CInputSystem::GetHapticsInterfaceAddress() const {
	AssertMsg( false, "TODO: `CInputSystem::GetHapticsInterfaceAddress()` not implemented" );
	return nullptr;
}

void CInputSystem::SetNovintPure( bool pPure ) {
	AssertMsg( false, "TODO: `CInputSystem::SetNovintPure( %d )` not implemented", pPure );
}

bool CInputSystem::GetRawMouseAccumulators( int& accumX, int& accumY ) {
	accumX = m_MouseAccX;
	m_MouseAccX = 0;

	accumY = m_MouseAccY;
	m_MouseAccY = 0;

	return true;
}

void CInputSystem::SetConsoleTextMode( const bool pConsoleTextMode ) {
	m_ConsoleTextMode = pConsoleTextMode;
}

namespace { CInputSystem s_InputSystem{}; }
EXPOSE_SINGLE_INTERFACE_GLOBALVAR( CInputSystem, IInputSystem, INPUTSYSTEM_INTERFACE_VERSION, s_InputSystem )

int CInputSystem::CMessagePumpThread::Run() {
	SDL_Event sdlEvent;
	while ( s_InputSystem.m_Running ) {
		while ( SDL_PollEvent( &sdlEvent ) ) {
			InputEvent_t inputEvent{};
			switch ( sdlEvent.type ) {
				case SDL_EventType::SDL_EVENT_QUIT:
					inputEvent.m_nType = InputEventType_t::IE_Quit;
					break;
				case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN:
					inputEvent.m_nType = InputEventType_t::IE_ButtonPressed;
					inputEvent.m_nData = sdlEvent.button.button;
					inputEvent.m_nTick = SDL_GetTicks();
					break;
				case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP:
					inputEvent.m_nType = InputEventType_t::IE_ButtonReleased;
					inputEvent.m_nData = sdlEvent.button.button;
					inputEvent.m_nTick = SDL_GetTicks();
					break;
				default:
					Warning( "Missing event: %d", sdlEvent.type );
			}

			s_InputSystem.m_EventQueue.Insert( inputEvent );
		}
	}
	return 0;
}
