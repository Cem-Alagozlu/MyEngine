#pragma once
#include "Blackboard.h"
#include "Structs.h"

namespace cem
{
	class GameObject;
	class PookaBlackboard final : public Blackboard
	{
	public:
		PookaBlackboard();
		~PookaBlackboard();



		std::weak_ptr<GameObject> m_pPooka;
		bool m_IsTeleporting = false;
		Vector2f m_Velocity;
		float m_Speed;
		float m_PumpedTimer;
		float m_RandomTeleportTimer;
		float m_MinTeleportTimer;
	};
}

