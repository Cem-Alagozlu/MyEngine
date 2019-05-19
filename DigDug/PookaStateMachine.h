#pragma once
#include "StateMachine.h"
#include "PookaBlackboard.h"
#include "PookaStateMove.h"

class PookaStateMachine final : public StateMachine
{
public:
	PookaStateMachine() = default;

	void Update() override;
	virtual void Initialize() override;
	PookaBlackboard& GetBlackboard();

private:
	//add states here
	PookaStateMove m_Move;

	PookaBlackboard m_Blackboard;
};

