#include "DigDugPCH.h"
#include "FygarStateMove.h"
#include "FygarBlackboard.h"
#include "Timing.h"
#include "Fygar.h"


namespace cem
{
	FygarStateMove::FygarStateMove()
	{
	}


	FygarStateMove::~FygarStateMove()
	{
	}

	void FygarStateMove::Enter()
	{

		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();
		GetBlackboard<FygarBlackboard>()->m_Speed = 2.0f;

		if (fygar)
		{
			GetBlackboard<FygarBlackboard>()->m_RandomTeleportTimer = float(rand() % 20 + 10);
			std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Fygar>(fygar)->GetFygarSprites(Fygar::FygarSprites::walking)->SetVisibility(true);
		}
	}

	void FygarStateMove::Exit()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();

		if (fygar)
		{
			std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
		}
	}

	void FygarStateMove::Update()
	{
		float& teleportTimer = GetBlackboard<FygarBlackboard>()->m_RandomTeleportTimer;

		teleportTimer -= Timing::GetInstance().GetDeltaTime();

		if (teleportTimer <= 0.0f)
		{
			GetBlackboard<FygarBlackboard>()->m_IsTeleporting = true;
		}
	}

	bool FygarStateMove::CanTransition()
	{
		if (!GetBlackboard<FygarBlackboard>()->m_IsTeleporting)
		{
			return true;
		}
		return false;
	}
}
