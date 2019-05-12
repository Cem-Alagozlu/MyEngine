#include "DigDugPCH.h"
#include "DigDugStateMachine.h"


void DigDugStateMachine::Update()
{
	StateMachine::Update();
}

void DigDugStateMachine::Initialize()
{
	m_Idle.Initialize(&m_Blackboard);
	m_Move.Initialize(&m_Blackboard);
	m_Pump.Initialize(&m_Blackboard);

	InitializeState(&m_Idle);

	//IDLE
	m_Idle.AddTransitionState(&m_Move);
	m_Idle.AddTransitionState(&m_Pump);

	//MOVE
	m_Move.AddTransitionState(&m_Idle);
	m_Move.AddTransitionState(&m_Pump);

	//PUMP
	m_Pump.AddTransitionState(&m_Move);
	m_Pump.AddTransitionState(&m_Idle);

}

DigDugBlackboard & DigDugStateMachine::GetBlackboard()
{
	return m_Blackboard;
}
