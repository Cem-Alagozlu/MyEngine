#pragma once

#include "Singleton.h"
//std::pair

namespace cem
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonUP,
		ButtonDown,
		ButtonLeft,
		ButtonRight,
		_Size
	};

	enum class InputTriggerState
	{
		Up,
		Down,
		Pressed,
		Released
	};



	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput();
		InputTriggerState IsPressed(ControllerButton button) const;

	private:
		InputTriggerState GetState(WORD button, SDL_Scancode keyboardKey) const;
		XINPUT_STATE m_CurrentState{}, m_PreviousState{};
		bool m_IsButtonDown;

		std::map<SDL_Scancode, bool> m_PrevKeyboardInput;
		std::map<SDL_Scancode, bool> m_CurrKeyboardInput;
	};

}