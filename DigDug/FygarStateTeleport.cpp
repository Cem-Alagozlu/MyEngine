#include "DigDugPCH.h"
#include "FygarStateTeleport.h"
#include "FygarBlackboard.h"
#include "Timing.h"
#include "Fygar.h"


namespace cem
{
	FygarStateTeleport::FygarStateTeleport()
	{
	}


	FygarStateTeleport::~FygarStateTeleport()
	{
	}

	void FygarStateTeleport::Enter()
	{
		GetBlackboard<FygarBlackboard>()->m_MinTeleportTimer = 3.0f;
		GetBlackboard<FygarBlackboard>()->m_Speed = 3.5f;
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();

		if (fygar)
		{
			GetBlackboard<FygarBlackboard>()->m_RandomTeleportTimer = 0.0f;
			std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Fygar>(fygar)->GetFygarSprites(Fygar::FygarSprites::teleporting)->SetVisibility(true);
		}
	}

	void FygarStateTeleport::Exit()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();

		if (fygar)
		{
			std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
		}
	}

	void FygarStateTeleport::Update()
	{
		float& minTeleportTime = GetBlackboard<FygarBlackboard>()->m_MinTeleportTimer;
		minTeleportTime -= Timing::GetInstance().GetDeltaTime();

		if (minTeleportTime <= 0.0f)
		{
			GetBlackboard<FygarBlackboard>()->m_IsTeleporting = false;
		}

	}

	bool FygarStateTeleport::CanTransition()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();

		if (fygar)
		{
			if (!std::dynamic_pointer_cast<Fygar>(fygar)->GettingPumped()
				&&
				GetBlackboard<FygarBlackboard>()->m_IsTeleporting
				&& 
				!GetBlackboard<FygarBlackboard>()->m_IsFiring)
			{
				return true;
			}
		}
		return false;
	}
}
