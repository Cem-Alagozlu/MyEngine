#pragma once
#include "Blackboard.h"
#include "Structs.h"


namespace cem
{
	class GameObject;
	class FygarBlackboard final : public Blackboard
	{
	public:
		FygarBlackboard();
		~FygarBlackboard();


		std::weak_ptr<GameObject> m_pFygar;
		bool m_IsTeleporting = false;
		Vector2f m_Velocity;
		float m_Speed;
		float m_RandomTeleportTimer;
		float m_MinTeleportTimer;
		float m_MinFireTime;
		float m_RandomFireTimer;
		bool m_IsFiring = false;
		bool m_IsBeingPumped;
		int m_PumpPhase;
		float m_PumpedTimer;
	};
}




