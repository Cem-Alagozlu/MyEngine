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
		std::cout << "idle\n";
	}

	bool DigDugStateIdle::CanTransition()
	{
		auto blackboard = GetBlackboard<DigDugBlackboard>();
		Vector2f velocity = blackboard->m_Velocity;
		bool isPumping = blackboard->m_IsPumping;
		bool isDigging = blackboard->m_IsDigging;
		bool isDead = blackboard->m_HasDied;
		if (velocity.x == 0 && velocity.y == 0 &&!isDigging && !isPumping &&!isDead)
		{
			return true;
		}
		return false;
	}
}