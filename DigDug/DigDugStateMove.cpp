#include "DigDugPCH.h"
#include "DigDugStateMove.h"
#include "DigDugBlackboard.h"
#include "SpriteComponent.h"
#include "Player.h"

DigDugStateMove::DigDugStateMove()
{
}


DigDugStateMove::~DigDugStateMove()
{
}

void DigDugStateMove::Enter()
{
	std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();

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
	Vector2f velocity = GetBlackboard<DigDugBlackboard>()->m_Velocity;
	std::shared_ptr<GameObject> player = GetBlackboard<DigDugBlackboard>()->m_pPlayer.lock();


	if (player)
	{
		auto sprite = player->GetComponent<SpriteComponent>();
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
		else if(velocity.y < 0.0f)
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

	std::cout << "MOVE STATE \n";

}

bool DigDugStateMove::CanTransition()
{
	Vector2f velocity = GetBlackboard<DigDugBlackboard>()->m_Velocity;

	if (!(velocity.x == 0) || !(velocity.y == 0))
	{
		return true;
	}
	return false;
}

