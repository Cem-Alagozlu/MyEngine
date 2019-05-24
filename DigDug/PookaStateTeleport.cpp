#include "DigDugPCH.h"
#include "PookaStateTeleport.h"
#include "DigDugBlackboard.h"
#include "PookaBlackboard.h"
#include "Pooka.h"
#include "Timing.h"

namespace cem
{
	PookaStateTeleport::PookaStateTeleport()
	{
	}


	PookaStateTeleport::~PookaStateTeleport()
	{
	}

	void PookaStateTeleport::Enter()
	{
		GetBlackboard<PookaBlackboard>()->m_MinTeleportTimer = 5.0f;
		GetBlackboard<PookaBlackboard>()->m_Speed = 3.5f;
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();

		if (pooka)
		{
			GetBlackboard<PookaBlackboard>()->m_RandomTeleportTimer = 0.0f;
			std::dynamic_pointer_cast<Pooka>(pooka)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Pooka>(pooka)->GetPookaSprites(Pooka::PookaSprites::teleporting)->SetVisibility(true);
		}
	}

	void PookaStateTeleport::Exit()
	{
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();

		if (pooka)
		{
			std::dynamic_pointer_cast<Pooka>(pooka)->SetSpritesInvisible();
		}
	}

	void PookaStateTeleport::Update()
	{
		float& minTeleportTime  = GetBlackboard<PookaBlackboard>()->m_MinTeleportTimer;
		minTeleportTime -= Timing::GetInstance().GetDeltaTime();

		if (minTeleportTime <= 0.0f)
		{
			GetBlackboard<PookaBlackboard>()->m_IsTeleporting = false;
		}

	}

	bool PookaStateTeleport::CanTransition()
	{
		bool isTeleporting = GetBlackboard<PookaBlackboard>()->m_IsTeleporting;

		if (isTeleporting)
		{
			return true;
		}
		return false;
	}
}
