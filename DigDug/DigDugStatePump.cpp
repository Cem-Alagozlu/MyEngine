#include "DigDugPCH.h"
#include "DigDugStatePump.h"
#include "DigDugBlackboard.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Timing.h"

namespace cem
{
	DigDugStatePump::~DigDugStatePump()
	{
	}

	void DigDugStatePump::Enter()
	{
		std::shared_ptr<GameObject> digdug = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (digdug)
		{
			GetBlackboard<DigDugBlackboard>()->m_PumpTimer = 1.0f;
			std::dynamic_pointer_cast<Player>(digdug)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Player>(digdug)->GetPlayerSprites(Player::PlayerSprites::pumping)->SetVisibility(true);
		}
	
	}

	void DigDugStatePump::Exit()
	{
		std::shared_ptr<GameObject> digdug = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (digdug)
		{
			GetBlackboard<DigDugBlackboard>()->m_PumpTimer = 0.0f;
			std::dynamic_pointer_cast<Player>(digdug)->SetSpritesInvisible();
		}
	}

	void DigDugStatePump::Update()
	{
		auto digdugBlackboard = GetBlackboard<DigDugBlackboard>();
		Vector2f velocity = digdugBlackboard->m_Velocity;
		std::shared_ptr<GameObject> player = digdugBlackboard->m_pPlayer.lock();
		digdugBlackboard->m_PumpTimer -= Timing::GetInstance().GetDeltaTime();


		if (player)
		{
			auto sprite = player->GetComponent<SpriteComponent>();
			if (velocity.x < 0.0f)
			{
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_HORIZONTAL);
			}
			else if (velocity.x > 0.0f)
			{
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_NONE);
			}
			else if (velocity.y < 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(-90.0);
			}
			else if (velocity.y > 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(90.0);
			}

		}

		if (digdugBlackboard->m_PumpTimer < 0.0f)
		{
			GetBlackboard<DigDugBlackboard>()->m_IsPumping = false;
		}
		
		std::cout << "pumptime: " << digdugBlackboard->m_PumpTimer << std::endl;

	}

	

	bool DigDugStatePump::CanTransition()
	{
		bool isPumping = GetBlackboard<DigDugBlackboard>()->m_IsPumping;

		if (isPumping)
		{
			return true;
		}

		return false;
	}
}
