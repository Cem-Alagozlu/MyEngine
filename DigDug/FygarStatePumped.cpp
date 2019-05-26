#include "DigDugPCH.h"
#include "FygarStatePumped.h"
#include "GameObject.h"
#include "FygarBlackboard.h"
#include "Fygar.h"
#include "Timing.h"
#include "PlayerData.h"

namespace cem
{
	FygarStatePumped::FygarStatePumped()
	{
	}


	FygarStatePumped::~FygarStatePumped()
	{
	}

	void FygarStatePumped::Enter()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();
		GetBlackboard<FygarBlackboard>()->m_Speed = 0.0f;
		GetBlackboard<FygarBlackboard>()->m_IsBeingPumped = true;
		GetBlackboard<FygarBlackboard>()->m_PumpedTimer = 2.0f;
		if (fygar)
		{
			std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Fygar>(fygar)->GetFygarBlowUpTextures(Fygar::FygarTextures::blowUpPhase01)->SetVisibility(true);
		}
	}

	void FygarStatePumped::Exit()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();
		if (fygar)
		{
			GetBlackboard<FygarBlackboard>()->m_IsBeingPumped = false;
			std::dynamic_pointer_cast<Fygar>(fygar)->SetTexturesInvisible();
			std::dynamic_pointer_cast<Fygar>(fygar)->GetFygarSprites(Fygar::FygarSprites::walking)->SetVisibility(true);
		}
	}

	void FygarStatePumped::Update()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();
		if (fygar)
		{
			float& timer = GetBlackboard<FygarBlackboard>()->m_PumpedTimer;
			GetBlackboard<FygarBlackboard>()->m_Velocity.x = 0.0f;
			GetBlackboard<FygarBlackboard>()->m_Velocity.y = 0.0f;
			GetBlackboard<FygarBlackboard>()->m_Speed = 0.0f;

			timer -= Timing::GetInstance().GetDeltaTime();

			std::cout << "timer: " << timer << std::endl;

			if (timer >= 8.0f)
			{
				GetBlackboard<FygarBlackboard>()->m_PumpPhase = 3;
			}
			if (timer <= 7.9f && timer >= 6.0f)
			{
				GetBlackboard<FygarBlackboard>()->m_PumpPhase = 2;
			}
			if (timer <= 6.9f && timer >= 4.0f)
			{
				GetBlackboard<FygarBlackboard>()->m_PumpPhase = 1;
			}
			if (timer <= 0.0f)
			{
				std::dynamic_pointer_cast<Fygar>(fygar)->SetGettingPumped(false);
				GetBlackboard<FygarBlackboard>()->m_PumpPhase = 0;
			}


			switch (GetBlackboard<FygarBlackboard>()->m_PumpPhase)
			{
			case 0:
				break;
			case 1:
				std::dynamic_pointer_cast<Fygar>(fygar)->SetTexturesInvisible();
				std::dynamic_pointer_cast<Fygar>(fygar)->GetFygarBlowUpTextures(Fygar::FygarTextures::blowUpPhase02)->SetVisibility(true);
				break;
			case 2:
				std::dynamic_pointer_cast<Fygar>(fygar)->SetTexturesInvisible();
				std::dynamic_pointer_cast<Fygar>(fygar)->GetFygarBlowUpTextures(Fygar::FygarTextures::blowUpPhase03)->SetVisibility(true);
				break;
			case 3:
				std::dynamic_pointer_cast<Fygar>(fygar)->SetTexturesInvisible();
				std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
				std::dynamic_pointer_cast<Fygar>(fygar)->SetDead(true);
				PlayerData::GetInstance().AddScore(500);
				break;
			}
		}
	}

	bool FygarStatePumped::CanTransition()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();


		if (fygar)
		{
			if (std::dynamic_pointer_cast<Fygar>(fygar)->GettingPumped())
			{
				return true;
			}
		}
		return false;
	}
}
