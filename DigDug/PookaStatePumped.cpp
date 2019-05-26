#include "DigDugPCH.h"
#include "PookaStatePumped.h"
#include "PookaBlackboard.h"
#include "Pooka.h"
#include "Timing.h"

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
		GetBlackboard<PookaBlackboard>()->m_PumpedTimer = 1.0f;
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

			std::dynamic_pointer_cast<Pooka>(pooka)->SetTexturesInvisible();

		}
	}

	void PookaStatePumped::Update()
	{
		std::cout << "being pumped \n";
		std::shared_ptr<GameObject> pooka = GetBlackboard<PookaBlackboard>()->m_pPooka.lock();
		if (pooka)
		{
			float timer = GetBlackboard<PookaBlackboard>()->m_PumpedTimer;
			GetBlackboard<PookaBlackboard>()->m_Velocity.x = 0.0f;
			GetBlackboard<PookaBlackboard>()->m_Velocity.y = 0.0f;
			GetBlackboard<PookaBlackboard>()->m_Speed = 0.0f;

			timer -= Timing::GetInstance().GetDeltaTime();

			std::cout << "timer " << timer << std::endl;
			if (timer <= 0.0f)
			{
				std::dynamic_pointer_cast<Pooka>(pooka)->SetGettingPumped(false);
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
