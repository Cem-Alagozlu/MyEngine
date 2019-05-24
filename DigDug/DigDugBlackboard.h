#pragma once
#include "Blackboard.h"
#include "Structs.h"
#include "GameObject.h"

namespace cem
{
	class DigDugBlackboard final : public Blackboard
	{
	public:

		DigDugBlackboard();
		~DigDugBlackboard();


		Vector2f m_Velocity;
		bool m_IsDigging;
		bool m_IsPumping;
		bool m_IsPumpingEnemy;
		int m_PumpPhase;
		float m_PumpTimer;
		std::weak_ptr<cem::GameObject> m_pPlayer;
	};
}
