#include "DigDugPCH.h"
#include "DigDugStateDead.h"
#include "GameObject.h"
#include "DigDugBlackboard.h"
#include "Player.h"
#include "PlayerData.h"

namespace cem
{
	DigDugStateDead::DigDugStateDead()
	{

	}

	DigDugStateDead::~DigDugStateDead()
	{
	}

	void DigDugStateDead::Enter()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (player)
		{
			std::dynamic_pointer_cast<Player>(player)->SetSpritesInvisible();
			std::dynamic_pointer_cast<Player>(player)->GetPlayerSprites(Player::PlayerSprites::dead)->SetVisibility(true);
		}
	}

	void DigDugStateDead::Exit()
	{
		PlayerData::GetInstance().SetLives(-1);
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (player)
		{
			std::dynamic_pointer_cast<Player>(player)->SetSpritesInvisible();
		}

	}

	void DigDugStateDead::Update()
	{
		std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

		if (player)
		{
			auto sprite = player->GetComponent<SpriteComponent>();
			GetBlackboard<DigDugBlackboard>()->m_Velocity = Vector2f{ 0.0f,0.0f };
			if (sprite->HasEnded())
			{
				GetBlackboard<DigDugBlackboard>()->m_HasDied = false;
			}

		}
		std::cout << "is dying bruh\n";
	}

	bool DigDugStateDead::CanTransition()
	{
		bool& isDead = GetBlackboard<DigDugBlackboard>()->m_HasDied;

		if (isDead)
		{
			return true;
			
		}
		return false;
	}
}

