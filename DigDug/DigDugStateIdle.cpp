#include "DigDugPCH.h"
#include "DigDugStateIdle.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "DigDugBlackboard.h"

DigDugStateIdle::~DigDugStateIdle()
{
}

void DigDugStateIdle::Enter()
{
	std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

	if (player)
	{
		auto sprite = player->GetComponent<SpriteComponent>();
		sprite->Lock();
	}
}

void DigDugStateIdle::Exit()
{
	std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

	if (player)
	{
		auto sprite = player->GetComponent<SpriteComponent>();
		sprite->Unlock();
	}
}

void DigDugStateIdle::Update()
{
}

bool DigDugStateIdle::CanTransition()
{
	Vector2f velocity = GetBlackboard<DigDugBlackboard>()->m_Velocity;
	if (velocity.x == 0 && velocity.y == 0)
	{
		return true;
	}
	return false;
}
