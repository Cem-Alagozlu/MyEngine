#pragma once
#include "StateMachine.h"
#include "FygarBlackboard.h"
#include "FygarStateMove.h"
#include "FygarStateTeleport.h"
#include "FygarStatePumped.h"
#include "FygarStateFire.h"

namespace cem
{
	class FygarStateMachine final : public StateMachine
	{
	public:
		FygarStateMachine() = default;

		void Update() override;
		virtual void Initialize() override;
		FygarBlackboard& GetBlackboard();
	private:
		FygarStateMove m_Move;
		FygarStateTeleport m_Teleport;
		FygarStatePumped m_Pumped;
		FygarStateFire m_Fire;
		FygarBlackboard m_Blackboard;
	};
}

