#include "MiniginPCH.h"
#include "StateMachine.h"

void StateMachine::Update()
{
	m_pState->Update();
	for (State* transitionState : m_pState->GetTransionStates())
	{
		if (transitionState->CanTransition())
		{
			Transit(transitionState);
			break;
		}
	}
}

void StateMachine::Transit(State * newState)
{
	m_pState->Exit();
	m_pState = newState;
	m_pState->Enter();
}

void StateMachine::InitializeState(State* initState)
{
	m_pState = initState;
	m_pState->Enter();
}
