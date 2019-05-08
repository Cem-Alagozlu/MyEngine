#include "MiniginPCH.h"
#include "InputManager.h"

bool InputManager::ProcessInput()
{
	m_PreviousState = m_CurrentState;

	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}
	
	return true;
}

InputTriggerState InputManager::IsPressed(ControllerButton button) const
{
	//m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	switch (button)
	{
	case ControllerButton::ButtonA:
		return GetState(XINPUT_GAMEPAD_A);
	case ControllerButton::ButtonB:
		return GetState(XINPUT_GAMEPAD_B);
	case ControllerButton::ButtonX:
		return GetState(XINPUT_GAMEPAD_X);
	case ControllerButton::ButtonY:
		return GetState(XINPUT_GAMEPAD_Y);
	case ControllerButton::ButtonUP:
		return GetState(XINPUT_GAMEPAD_DPAD_UP);
	case ControllerButton::ButtonDown:
		return GetState(XINPUT_GAMEPAD_DPAD_DOWN);
	case ControllerButton::ButtonLeft:
		return GetState(XINPUT_GAMEPAD_DPAD_LEFT);
	case ControllerButton::ButtonRight:
		return GetState(XINPUT_GAMEPAD_DPAD_RIGHT);
	default:
		return InputTriggerState::Up;
	}
}

InputTriggerState InputManager::GetState(WORD button) const
{
	bool prevKey = m_PreviousState.Gamepad.wButtons & button;
	bool currKey = m_CurrentState.Gamepad.wButtons & button;

	if (prevKey)
	{
		if (currKey)
		{
			return InputTriggerState::Down;
		}
		else
		{
			return InputTriggerState::Released;
		}
	}
	else
	{
		if (currKey)
		{
			return InputTriggerState::Pressed;
		}
		else
		{
			return InputTriggerState::Up;
		}
	} 
}