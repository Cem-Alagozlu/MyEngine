#pragma once
#include "DigDugStateIdle.h"
#include "DigDugStateMove.h"
#include "StateMachine.h"
#include "DigDugBlackboard.h"
#include "DigDugStatePump.h"
#include "DigDugStateDig.h"
#include "DigDugStateDead.h"

namespace cem
{

	class DigDugStateMachine final : public StateMachine
	{
	public:
		DigDugStateMachine() = default;

		void Update() override;
		virtual void Initialize() override;
		DigDugBlackboard& GetBlackboard();

	private:
		DigDugStateIdle m_Idle;
		DigDugStateMove m_Move;
		DigDugStatePump m_Pump;
		DigDugStateDig m_Dig;
		DigDugStateDead m_Dead;
		DigDugBlackboard m_Blackboard;
	};
}

