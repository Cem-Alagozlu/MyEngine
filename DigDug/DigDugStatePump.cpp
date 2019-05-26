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
		auto digdugBlackboard = GetBlackboard<DigDugBlackboard>();
		std::shared_ptr<GameObject> digdug = digdugBlackboard->m_pPlayer.lock();
		if (digdug)
		{
			digdugBlackboard->m_PumpTimer = 1.0f;
			std::dynamic_pointer_cast<Player>(digdug)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Player>(digdug)->GetPlayerSprites(Player::PlayerSprites::pumping)->SetVisibility(true);

			auto sprite = std::dynamic_pointer_cast<Player>(digdug)->GetPlayerSprites(Player::PlayerSprites::pumping);
			switch (digdugBlackboard->m_Direction)
			{
			case DigDugBlackboard::Direction::right:
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_NONE);
				sprite->SetOffset(Vector2f{ 0.0f,0.0f });
				break;
			case DigDugBlackboard::Direction::left:;
				sprite->SetAngle(0.0);
				sprite->SetOffset(Vector2f{ -40.0f,0.0f });
				sprite->FlipTexture(SDL_FLIP_HORIZONTAL);
				break;
			case DigDugBlackboard::Direction::down:
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(-90.0f);
				sprite->SetOffset(Vector2f{ -30.0f,-30.0f });
				break;
			case DigDugBlackboard::Direction::up:
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(90.0);
				sprite->SetOffset(Vector2f{ -20.0f,30.0f });
				break;
			}

		}

	
	}

	void DigDugStatePump::Exit()
	{
		std::shared_ptr<GameObject> digdug = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (digdug)
		{
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

			switch (digdugBlackboard->m_Direction)
			{
			case DigDugBlackboard::Direction::right:
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_NONE);
				sprite->SetOffset(Vector2f{ 0.0f,0.0f });
				break;
			case DigDugBlackboard::Direction::left:;
				sprite->SetAngle(0.0);
				sprite->SetOffset(Vector2f{ -40.0f,0.0f });
				sprite->FlipTexture(SDL_FLIP_HORIZONTAL);
				break;
			case DigDugBlackboard::Direction::down:
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(-90.0f);
				sprite->SetOffset(Vector2f{ -30.0f,-30.0f });
				break;
			case DigDugBlackboard::Direction::up:
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(90.0);
				sprite->SetOffset(Vector2f{ -20.0f,30.0f });
				break;
			}

		}

		if (digdugBlackboard->m_PumpTimer < 0.0f)
		{
			digdugBlackboard->m_IsPumping = false;
		}



		digdugBlackboard->m_Velocity.x = 0.0f;
		digdugBlackboard->m_Velocity.y = 0.0f;
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
