#pragma once
#include "DigDugStateIdle.h"
#include "DigDugStateMove.h"
#include "StateMachine.h"
#include "DigDugBlackboard.h"

class DigDugStateMachine final : public StateMachine
{
public:
	DigDugStateMachine();

	void Update() override;

private:
	DigDugStateIdle m_Idle;
	DigDugStateMove m_Move;

	DigDugBlackboard m_Blackboard;
};

