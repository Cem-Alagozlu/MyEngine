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

		InitializeState(&m_Move);

		//MOVE
		m_Move.AddTransitionState(&m_Teleport);

		//TELEPORT
		m_Teleport.AddTransitionState(&m_Move);

	}

	FygarBlackboard& FygarStateMachine::GetBlackboard()
	{
		return m_Blackboard;
	}
}