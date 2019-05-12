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
	std::cout << "IDLE STATE \n";
}

bool DigDugStateIdle::CanTransition()
{
	Vector2f velocity = GetBlackboard<DigDugBlackboard>()->m_Velocity;
	std::cout << "Velocity X: " << velocity.x << "Velocity Y: " << velocity.y << std::endl;

	if (velocity.x == 0 && velocity.y == 0)
	{
		return true;
	}
	return false;
}
