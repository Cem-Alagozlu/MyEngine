#include "MiniginPCH.h"
#include "State.h"

void State::Initialize(Blackboard * blackboard)
{
	m_pBlackboard = blackboard;
}

void State::AddTransitionState(State* state)
{
	m_pStates.push_back(state);
}

const std::vector<State*>& State::GetTransionStates()
{
	return m_pStates;
}
