#include "DigDugPCH.h"
#include "DigDugStateMachine.h"


DigDugStateMachine::DigDugStateMachine()
{
	m_Idle.Initialize(&m_Blackboard);
	m_Move.Initialize(&m_Blackboard);

	Initialize(&m_Idle);
	m_Idle.AddTransitionState(&m_Move);
	m_Move.AddTransitionState(&m_Idle);
}

void DigDugStateMachine::Update()
{
	StateMachine::Update();
}
