#include "DigDugPCH.h"
#include "FygarStateFire.h"
#include "FygarBlackboard.h"
#include "Fygar.h"
#include "Timing.h"

namespace cem
{

	FygarStateFire::FygarStateFire()
	{
	}


	FygarStateFire::~FygarStateFire()
	{
	}

	void FygarStateFire::Enter()
	{
		GetBlackboard<FygarBlackboard>()->m_MinFireTime = 3.0f;
		GetBlackboard<FygarBlackboard>()->m_Speed = 0.0f;
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();

		if (fygar)
		{
			GetBlackboard<FygarBlackboard>()->m_RandomFireTimer = 0.0f;
			std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Fygar>(fygar)->GetFygarSprites(Fygar::FygarSprites::fire)->SetVisibility(true);
		}
	}

	void FygarStateFire::Exit()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();

		if (fygar)
		{
			std::dynamic_pointer_cast<Fygar>(fygar)->SetSpritesInvisible();
		}
	}

	void FygarStateFire::Update()
	{
		float& minFireTime = GetBlackboard<FygarBlackboard>()->m_MinFireTime;
		minFireTime -= Timing::GetInstance().GetDeltaTime();
		GetBlackboard<FygarBlackboard>()->m_Velocity.x = 0.0f;
		GetBlackboard<FygarBlackboard>()->m_Velocity.y = 0.0f;
		std::cout << "Fire\n";
		if (minFireTime <= 0.0f)
		{
			GetBlackboard<FygarBlackboard>()->m_IsFiring = false;
		}

	}

	bool FygarStateFire::CanTransition()
	{
		std::shared_ptr<GameObject> fygar = GetBlackboard<FygarBlackboard>()->m_pFygar.lock();

		if (fygar)
		{
			if (!std::dynamic_pointer_cast<Fygar>(fygar)->GettingPumped()
				&&
				GetBlackboard<FygarBlackboard>()->m_IsFiring
				&&
				!GetBlackboard<FygarBlackboard>()->m_IsTeleporting)
			{
				return true;
			}
		}
		return false;
	}
}
