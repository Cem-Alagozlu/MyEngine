#include "DigDugPCH.h"
#include "DigDugStateMachine.h"

namespace cem
{
	void DigDugStateMachine::Update()
	{
		StateMachine::Update();
	}

	void DigDugStateMachine::Initialize()
	{
		m_Idle.Initialize(&m_Blackboard);
		m_Move.Initialize(&m_Blackboard);
		m_Pump.Initialize(&m_Blackboard);
		m_Dig.Initialize(&m_Blackboard);

		InitializeState(&m_Idle);

		//IDLE
		m_Idle.AddTransitionState(&m_Move);
		m_Idle.AddTransitionState(&m_Pump);
		m_Idle.AddTransitionState(&m_Dig);

		//MOVE
		m_Move.AddTransitionState(&m_Idle);
		m_Move.AddTransitionState(&m_Pump);
		m_Move.AddTransitionState(&m_Dig);

		//PUMP
		m_Pump.AddTransitionState(&m_Move);
		m_Pump.AddTransitionState(&m_Idle);
		m_Pump.AddTransitionState(&m_Dig);

		//DIG
		m_Dig.AddTransitionState(&m_Move);
		m_Dig.AddTransitionState(&m_Pump);
		m_Dig.AddTransitionState(&m_Idle);
	}


	DigDugBlackboard & DigDugStateMachine::GetBlackboard()
	{
		return m_Blackboard;
	}
}
