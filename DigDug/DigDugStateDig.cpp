#include "DigDugPCH.h"
#include "DigDugStateDig.h"
#include "DigDugBlackboard.h"
#include "SpriteComponent.h"
#include "Player.h"

namespace cem
{

	DigDugStateDig::DigDugStateDig()
	{
	}


	DigDugStateDig::~DigDugStateDig()
	{
	}

	void DigDugStateDig::Enter()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();
		std::dynamic_pointer_cast<Player>(player)->SetSpritesInvisible();
		std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::digging)->SetVisibility(true);

		if (player)
		{
			auto sprite = player->GetComponent<SpriteComponent>();
			sprite->Unlock();
		}
	}

	void DigDugStateDig::Exit()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (player)
		{
			std::dynamic_pointer_cast<Player>(player)->SetSpritesInvisible();
		}
		GetBlackboard<DigDugBlackboard>()->m_IsDigging = false;
	}

	void DigDugStateDig::Update()
	{
		auto digdugBlackboard = GetBlackboard<DigDugBlackboard>();
		Vector2f velocity = digdugBlackboard->m_Velocity;
		std::shared_ptr<GameObject> player = digdugBlackboard->m_pPlayer.lock();

		if (player)
		{
			auto sprite = std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::digging);
			if (velocity.x < 0.0f)
			{
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_HORIZONTAL);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::left;
			}
			 if (velocity.x > 0.0f)
			{
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_NONE);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::right;

			}
			 if (velocity.y < 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(-90.0);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::down;
				
			}
			 if (velocity.y > 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(90.0);
				digdugBlackboard->m_Direction = DigDugBlackboard::Direction::up;
			}

		}

	}

	bool DigDugStateDig::CanTransition()
	{
		auto blackboard = GetBlackboard<DigDugBlackboard>();
		Vector2f velocity = blackboard->m_Velocity;
		bool isDigging = blackboard->m_IsDigging;


		if (isDigging && !(velocity.x == 0) || isDigging && !(velocity.y == 0))
		{
			return true;
		}

		return false;
	}
}
