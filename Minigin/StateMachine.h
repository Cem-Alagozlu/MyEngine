#pragma once
#include "State.h"

class StateMachine
{
public:
	StateMachine() = default;
	virtual ~StateMachine() = default;


	virtual void Update();
	virtual void Initialize() = 0;

protected:
	void Transit(State* newState);
	void InitializeState(State* initState);

private:
	Blackboard* m_pBlackboard;
	State* m_pState;
};
