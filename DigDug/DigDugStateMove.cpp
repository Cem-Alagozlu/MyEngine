#include "DigDugPCH.h"
#include "DigDugStateMove.h"
#include "DigDugBlackboard.h"
#include "SpriteComponent.h"
#include "Player.h"

namespace cem
{

	DigDugStateMove::DigDugStateMove()
	{
	}


	DigDugStateMove::~DigDugStateMove()
	{
	}

	void DigDugStateMove::Enter()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();
		std::dynamic_pointer_cast<Player>(player)->SetSpritesInvisible();
		std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::walking)->SetVisibility(true);

		if (player)
		{
			auto sprite = player->GetComponent<SpriteComponent>();
			sprite->Unlock();
		}
	}

	void DigDugStateMove::Exit()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (player)
		{
			auto sprite = player->GetComponent<SpriteComponent>();
			sprite->Lock();
		}
	}

	void DigDugStateMove::Update()
	{
		auto digdugBlackboard = GetBlackboard<DigDugBlackboard>();
		Vector2f velocity = digdugBlackboard->m_Velocity;
		std::cout << "moving\n";
		std::shared_ptr<GameObject> player = digdugBlackboard->m_pPlayer.lock();

		if (player)
		{
			auto sprite = std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::walking);
			if (velocity.x < 0.0f)
			{
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_HORIZONTAL);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::right;
			}
			else if (velocity.x > 0.0f)
			{
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_NONE);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::left;
			}
			else if (velocity.y < 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(-90.0);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::down;
			}
			else if (velocity.y > 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(90.0);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::up;
			}

		}
	}

	bool DigDugStateMove::CanTransition()
	{
		Vector2f velocity = GetBlackboard<DigDugBlackboard>()->m_Velocity;
		bool isDigging = GetBlackboard<DigDugBlackboard>()->m_IsDigging;
		bool isDead = GetBlackboard<DigDugBlackboard>()->m_HasDied;

		if (!(velocity.x == 0) || !(velocity.y == 0) && !isDigging &&!isDead)
		{
			return true;
		}
		return false;
	}

}