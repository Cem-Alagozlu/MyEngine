#include "DigDugPCH.h"
#include "PookaStateMachine.h"

namespace cem
{
	void PookaStateMachine::Update()
	{
		StateMachine::Update();
	}

	void PookaStateMachine::Initialize()
	{
		m_Move.Initialize(&m_Blackboard);
		m_Teleport.Initialize(&m_Blackboard);

		InitializeState(&m_Move);

		//MOVE
		m_Move.AddTransitionState(&m_Teleport);

		//TELEPORT
		m_Teleport.AddTransitionState(&m_Move);

	}

	PookaBlackboard& PookaStateMachine::GetBlackboard()
	{
		return m_Blackboard;
	}
}