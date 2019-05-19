#include "DigDugPCH.h"
#include "PookaStateMachine.h"


void PookaStateMachine::Update()
{
	StateMachine::Update();
}

void PookaStateMachine::Initialize()
{
	//m_Idle.Initialize(&m_Blackboard);
}

PookaBlackboard& PookaStateMachine::GetBlackboard()
{
	return m_Blackboard;
}
