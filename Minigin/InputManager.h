#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"



enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonUP,
		ButtonDown,
		ButtonLeft,
		ButtonRight
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
		bool ProcessInput();
		InputTriggerState IsPressed(ControllerButton button) const;
	private:
		InputTriggerState GetState(WORD button) const;
		XINPUT_STATE m_CurrentState{},m_PreviousState{};
		bool m_IsButtonDown;
	};
