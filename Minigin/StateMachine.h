#pragma once
#include "State.h"

class StateMachine
{
public:
	StateMachine() = default;
	virtual ~StateMachine() = default;

	virtual void Update();

protected:
	void Transit(State* newState);
	void Initialize(State* initState);

private:
	Blackboard* m_pBlackboard;
	State* m_pState;
};
