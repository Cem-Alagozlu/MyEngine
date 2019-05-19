#include "DigDugPCH.h"
#include "PookaStateMachine.h"


void PookaStateMachine::Update()
{
	StateMachine::Update();
}

void PookaStateMachine::Initialize()
{
	m_Move.Initialize(&m_Blackboard);

	InitializeState(&m_Move);
}

PookaBlackboard& PookaStateMachine::GetBlackboard()
{
	return m_Blackboard;
}
