#pragma once
#include "Blackboard.h"
#include "Structs.h"
#include "GameObject.h"

namespace cem
{
	class DigDugBlackboard final : public Blackboard
	{
	public:
		enum class Direction : int
		{
			left = 0,
			right = 1,
			up = 2,
			down = 3
		};

		DigDugBlackboard();
		~DigDugBlackboard();


		Vector2f m_Velocity;
		bool m_IsDigging;
		bool m_IsPumping;
		bool m_IsPumpingEnemy;
		int m_PumpPhase;
		float m_PumpTimer;
		Direction m_Direction;
		bool m_HasDied = false;
		bool m_GameOver;
		std::weak_ptr<cem::GameObject> m_pPlayer;
	};
}
