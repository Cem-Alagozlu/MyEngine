#include "DigDugPCH.h"
#include "DigDugStateMove.h"
#include "InputManager.h"
#include "DigDugBlackboard.h"

DigDugStateMove::DigDugStateMove()
{
}


DigDugStateMove::~DigDugStateMove()
{
}

void DigDugStateMove::Enter()
{
	std::cout << "Enter!" << typeid(this).name() << std::endl; ;
}

void DigDugStateMove::Exit()
{
	std::cout << "Exit!" << typeid(this).name() << std::endl; ;
}

void DigDugStateMove::Update()
{
	std::cout << GetBlackboard<DigDugBlackboard>()->TotalSteps << std::endl;
	GetBlackboard<DigDugBlackboard>()->TotalSteps++;
}

bool DigDugStateMove::CanTransition()
{
	if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonDown) == InputTriggerState::Down)
	{
		return true;
	}
	return false;
}
