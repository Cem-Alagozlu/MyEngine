#pragma once
#include "StateMachine.h"
#include "PookaBlackboard.h"

class PookaStateMachine final : public StateMachine
{
public:
	PookaStateMachine() = default;

	void Update() override;
	virtual void Initialize() override;
	PookaBlackboard& GetBlackboard();

private:
	//add states here

	PookaBlackboard m_Blackboard;
};

