#include "DigDugPCH.h"
#include "DigDugStateIdle.h"
#include "InputManager.h"

DigDugStateIdle::~DigDugStateIdle()
{
}

void DigDugStateIdle::Enter()
{
	std::cout << "Enter!" << typeid(this).name() << std::endl; ;
}

void DigDugStateIdle::Exit()
{
	 std::cout << "Exit!" << typeid(this).name() << std::endl; ;
}

void DigDugStateIdle::Update()
{
	std::cout << "Update!" << typeid(this).name() << std::endl; ;
}

bool DigDugStateIdle::CanTransition()
{
	if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonDown) == InputTriggerState::Down)
	{
		return false;
	}
	return true;

}
