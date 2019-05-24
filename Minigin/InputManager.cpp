#include "MiniginPCH.h"
#include "InputManager.h"

namespace cem
{
	InputManager::InputManager()
	{
		m_CurrKeyboardInput[SDL_SCANCODE_UP] = false;
		m_CurrKeyboardInput[SDL_SCANCODE_LEFT] = false;
		m_CurrKeyboardInput[SDL_SCANCODE_RIGHT] = false;
		m_CurrKeyboardInput[SDL_SCANCODE_DOWN] = false;
		m_CurrKeyboardInput[SDL_SCANCODE_X] = false;
		m_CurrKeyboardInput[SDL_SCANCODE_Y] = false;
		m_CurrKeyboardInput[SDL_SCANCODE_Z] = false;
		m_CurrKeyboardInput[SDL_SCANCODE_G] = false;
	}

	bool InputManager::ProcessInput()
	{
		m_PreviousState = m_CurrentState;
		m_PrevKeyboardInput = m_CurrKeyboardInput;
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentState);

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) 
			{
				m_CurrKeyboardInput[e.key.keysym.scancode] = true;
			}
			else if (e.type == SDL_KEYUP)
			{
				m_CurrKeyboardInput[e.key.keysym.scancode] = false;
			}
		}

		return true;
	}

	InputTriggerState InputManager::IsPressed(ControllerButton button) const
	{
		//m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;

		//return (m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button)) ! = 0:

		switch (button)
		{
		case ControllerButton::ButtonA:
			return GetState(XINPUT_GAMEPAD_A,SDL_SCANCODE_X);
		case ControllerButton::ButtonB:
			return GetState(XINPUT_GAMEPAD_B, SDL_SCANCODE_Y);
		case ControllerButton::ButtonX:
			return GetState(XINPUT_GAMEPAD_X, SDL_SCANCODE_Z);
		case ControllerButton::ButtonY:
			return GetState(XINPUT_GAMEPAD_Y, SDL_SCANCODE_G);
		case ControllerButton::ButtonUP:
			return GetState(XINPUT_GAMEPAD_DPAD_UP,SDL_SCANCODE_UP);
		case ControllerButton::ButtonDown:
			return GetState(XINPUT_GAMEPAD_DPAD_DOWN, SDL_SCANCODE_DOWN);
		case ControllerButton::ButtonLeft:
			return GetState(XINPUT_GAMEPAD_DPAD_LEFT, SDL_SCANCODE_LEFT);
		case ControllerButton::ButtonRight:
			return GetState(XINPUT_GAMEPAD_DPAD_RIGHT, SDL_SCANCODE_RIGHT);
		default:
			return InputTriggerState::Up;
		}
	}

	InputTriggerState InputManager::GetState(WORD button, SDL_Scancode keyboardKey) const
	{
		bool prevKey = m_PreviousState.Gamepad.wButtons & button || m_PrevKeyboardInput.at(keyboardKey);
		bool currKey = m_CurrentState.Gamepad.wButtons & button || m_CurrKeyboardInput.at(keyboardKey);
		
		
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
}