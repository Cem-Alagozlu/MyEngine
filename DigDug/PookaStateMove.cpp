#include "DigDugPCH.h"
#include "PookaStateMove.h"
#include "SpriteComponent.h"
#include "PookaBlackboard.h"
#include "Pooka.h"
#include "Timing.h"

namespace cem
{
	PookaStateMove::PookaStateMove()
	{
	}


	PookaStateMove::~PookaStateMove()
	{
	}

	void PookaStateMove::Enter()
	{

		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();
		GetBlackboard<PookaBlackboard>()->m_Speed = 2.0f;

		if (pooka)
		{
			GetBlackboard<PookaBlackboard>()->m_RandomTeleportTimer = float(rand() % 15 + 10);
			std::dynamic_pointer_cast<Pooka>(pooka)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Pooka>(pooka)->GetPookaSprites(Pooka::PookaSprites::walking)->SetVisibility(true);
		}
	}

	void PookaStateMove::Exit()
	{
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();

		if (pooka)
		{
			std::dynamic_pointer_cast<Pooka>(pooka)->SetSpritesInvisible();
		}
	}

	void PookaStateMove::Update()
	{
		float& teleportTimer = GetBlackboard<PookaBlackboard>()->m_RandomTeleportTimer;

		teleportTimer -= Timing::GetInstance().GetDeltaTime();

		if (teleportTimer <= 0.0f)
		{
			GetBlackboard<PookaBlackboard>()->m_IsTeleporting = true;
		}
		std::cout << "moving Pooka\n";
	}

	bool PookaStateMove::CanTransition()
	{
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();

		if (pooka)
		{
			if (!std::dynamic_pointer_cast<Pooka>(pooka)->GettingPumped()
				&&
				!GetBlackboard<PookaBlackboard>()->m_IsTeleporting)
			{
				return true;
			}
		}
		return false;
	}
}
