#include "DigDugPCH.h"
#include "PookaStatePumped.h"
#include "PookaBlackboard.h"
#include "Pooka.h"
#include "Timing.h"
#include "PlayerData.h"

namespace cem
{
	PookaStatePumped::PookaStatePumped()
	{
	}


	PookaStatePumped::~PookaStatePumped()
	{
	}

	void PookaStatePumped::Enter()
	{
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();
		GetBlackboard<PookaBlackboard>()->m_Speed = 0.0f;
		GetBlackboard<PookaBlackboard>()->m_IsBeingPumped = true;
		GetBlackboard<PookaBlackboard>()->m_PumpedTimer = 2.0f;
		if (pooka)
		{	
			std::dynamic_pointer_cast<Pooka>(pooka)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Pooka>(pooka)->GetPookaBlowUpTextures(Pooka::PookaTextures::blowUpPhase01)->SetVisibility(true);
		}
	}

	void PookaStatePumped::Exit()
	{
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();
		if (pooka)
		{
			GetBlackboard<PookaBlackboard>()->m_IsBeingPumped = false;
			std::dynamic_pointer_cast<Pooka>(pooka)->SetTexturesInvisible();
			std::dynamic_pointer_cast<Pooka>(pooka)->GetPookaSprites(Pooka::PookaSprites::walking)->SetVisibility(true);
		}
	}

	void PookaStatePumped::Update()
	{
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();
		if (pooka)
		{
			float& timer = GetBlackboard<PookaBlackboard>()->m_PumpedTimer;
			GetBlackboard<PookaBlackboard>()->m_Velocity.x = 0.0f;
			GetBlackboard<PookaBlackboard>()->m_Velocity.y = 0.0f;
			GetBlackboard<PookaBlackboard>()->m_Speed = 0.0f;

			timer -= Timing::GetInstance().GetDeltaTime();

			std::cout << "timer: " << timer << std::endl;

			if (timer >= 8.0f)
			{
				GetBlackboard<PookaBlackboard>()->m_PumpPhase = 3;
			}
			if (timer <= 7.9f && timer >= 6.0f)
			{
				GetBlackboard<PookaBlackboard>()->m_PumpPhase = 2;
			}
			if (timer <= 6.9f && timer >= 4.0f)
			{
				GetBlackboard<PookaBlackboard>()->m_PumpPhase = 1;
			}
			if (timer <= 0.0f)
			{
				std::dynamic_pointer_cast<Pooka>(pooka)->SetGettingPumped(false);
				GetBlackboard<PookaBlackboard>()->m_PumpPhase = 0;
			}


			switch (GetBlackboard<PookaBlackboard>()->m_PumpPhase)
			{
			case 0:
				break;
			case 1:
				std::dynamic_pointer_cast<Pooka>(pooka)->SetTexturesInvisible();
				std::dynamic_pointer_cast<Pooka>(pooka)->GetPookaBlowUpTextures(Pooka::PookaTextures::blowUpPhase02)->SetVisibility(true);
				break;
			case 2:
				std::dynamic_pointer_cast<Pooka>(pooka)->SetTexturesInvisible();
				std::dynamic_pointer_cast<Pooka>(pooka)->GetPookaBlowUpTextures(Pooka::PookaTextures::blowUpPhase03)->SetVisibility(true);
				break;
			case 3:
				std::dynamic_pointer_cast<Pooka>(pooka)->SetTexturesInvisible();
				std::dynamic_pointer_cast<Pooka>(pooka)->SetSpritesInvisible();
				std::dynamic_pointer_cast<Pooka>(pooka)->SetDead(true);
				PlayerData::GetInstance().AddScore(500);
				break;
			}
		}
	}

	bool PookaStatePumped::CanTransition()
	{
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();
		

		if (pooka)
		{
			if (std::dynamic_pointer_cast<Pooka>(pooka)->GettingPumped())
			{
				return true;
			}
		}
		return false;
	}
}
