#include "DigDugPCH.h"
#include "FygarStateMachine.h"

namespace cem
{
	void FygarStateMachine::Update()
	{
		StateMachine::Update();
	}

	void FygarStateMachine::Initialize()
	{
		m_Move.Initialize(&m_Blackboard);
		m_Teleport.Initialize(&m_Blackboard);
		m_Pumped.Initialize(&m_Blackboard);
		m_Fire.Initialize(&m_Blackboard);


		InitializeState(&m_Move);

		//MOVE
		m_Move.AddTransitionState(&m_Teleport);
		m_Move.AddTransitionState(&m_Pumped);
		m_Move.AddTransitionState(&m_Fire);

		//TELEPORT
		m_Teleport.AddTransitionState(&m_Move);
		m_Teleport.AddTransitionState(&m_Pumped);
		m_Teleport.AddTransitionState(&m_Fire);

		//FIRE
		m_Fire.AddTransitionState(&m_Move);
		m_Fire.AddTransitionState(&m_Pumped);
		m_Fire.AddTransitionState(&m_Teleport);

		//PUMPED
		m_Pumped.AddTransitionState(&m_Move);
		m_Pumped.AddTransitionState(&m_Teleport);

	}

	FygarBlackboard& FygarStateMachine::GetBlackboard()
	{
		return m_Blackboard;
	}
}