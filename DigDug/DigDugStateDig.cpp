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
			}
			 if (velocity.x > 0.0f)
			{
				sprite->SetAngle(0.0);
				sprite->FlipTexture(SDL_FLIP_NONE);

			}
			 if (velocity.y < 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(-90.0);
				
			}
			 if (velocity.y > 0.0f)
			{
				sprite->FlipTexture(SDL_FLIP_VERTICAL);
				sprite->SetAngle(90.0);
				
			}

		}

	}

	bool DigDugStateDig::CanTransition()
	{
		auto blackboard = GetBlackboard<DigDugBlackboard>();
		Vector2f velocity = blackboard->m_Velocity;
		bool isDigging = blackboard->m_IsDigging;
		bool isPumping = blackboard->m_IsPumping;
		bool isDead = blackboard->m_HasDied;

		if (isDigging && !isPumping && !(velocity.x == 0) || !(velocity.y == 0) &&!isDead)
		{
			return true;
		}

		return false;
	}
}
