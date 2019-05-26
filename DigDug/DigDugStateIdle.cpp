#include "DigDugPCH.h"
#include "DigDugStateIdle.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "DigDugBlackboard.h"

namespace cem
{

	DigDugStateIdle::~DigDugStateIdle()
	{
	}

	void DigDugStateIdle::Enter()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (player)
		{
			std::dynamic_pointer_cast<Player>(player)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::walking)->SetVisibility(true);
			auto sprite = player->GetComponent<SpriteComponent>();
			sprite->Lock();
		}
	}

	void DigDugStateIdle::Exit()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (player)
		{
			std::dynamic_pointer_cast<Player>(player)->SetSpritesInvisible();
			auto sprite = player->GetComponent<SpriteComponent>();
			sprite->Unlock();
		}
	}

	void DigDugStateIdle::Update()
	{
	}

	bool DigDugStateIdle::CanTransition()
	{
		auto blackboard = GetBlackboard<DigDugBlackboard>();
		Vector2f velocity = blackboard->m_Velocity;
		bool isPumping = blackboard->m_IsPumping;

		if (!isPumping && velocity.x == 0 && velocity.y == 0)
		{
			return true;
		}
		return false;
	}
}