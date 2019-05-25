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
		std::shared_ptr<GameObject> player = digdugBlackboard->m_pPlayer.lock();

		digdugBlackboard->m_PumpTimer -= Timing::GetInstance().GetDeltaTime();

		
		if (player)
		{
			auto sprite = std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::pumping);
			auto currPos = player->GetComponent<TransformComponent>()->GetPosition();
			Vector2f newPos = currPos;

			switch (digdugBlackboard->m_Direction)
			{
			case DigDugBlackboard::Direction::left:
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_NONE);
				break;
			case DigDugBlackboard::Direction::right:
				sprite->SetAngle(180.0f);
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				break;
			case DigDugBlackboard::Direction::up:
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(90.0);
				break;
			case DigDugBlackboard::Direction::down:
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(-90.0);
				break;
			}

		}

		if (digdugBlackboard->m_PumpTimer < 0.0f)
		{
			GetBlackboard<DigDugBlackboard>()->m_IsPumping = false;
		}
		
		std::cout << "pumptime: " << digdugBlackboard->m_PumpTimer << std::endl;


		GetBlackboard<DigDugBlackboard>()->m_Velocity.x = 0.0f;
		GetBlackboard<DigDugBlackboard>()->m_Velocity.y = 0.0f;
	}

	

	bool DigDugStatePump::CanTransition()
	{
		bool isPumping = GetBlackboard<DigDugBlackboard>()->m_IsPumping;
		bool isDead = GetBlackboard<DigDugBlackboard>()->m_HasDied;
		if (isPumping && !isDead)
		{
			return true;
		}

		return false;
	}
}
