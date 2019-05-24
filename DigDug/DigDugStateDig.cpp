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
	}

	void DigDugStateDig::Update()
	{
		Vector2f velocity = GetBlackboard<DigDugBlackboard>()->m_Velocity;
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();


		if (player)
		{
			auto sprite = std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::digging);
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

	}

	bool DigDugStateDig::CanTransition()
	{
		bool isDigging = GetBlackboard<DigDugBlackboard>()->m_IsDigging;

		if (isDigging)
		{
			return true;
		}

		return false;
	}
}
