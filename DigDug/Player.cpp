#include "DigDugPCH.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "CommandManager.h"
#include "Timing.h"
#include "CollisionComponent.h"
#include "Tunnel.h"

namespace cem
{

	Player::Player()
	{
		m_Speed = 100;
		m_IsButtonPressed = false;

		CommandManager::GetInstance().AddCallBack(std::bind(&Player::MoveUp, this), CommandManager::InputCommands::moveUp);
		CommandManager::GetInstance().AddCallBack(std::bind(&Player::MoveDown, this), CommandManager::InputCommands::moveDown);
		CommandManager::GetInstance().AddCallBack(std::bind(&Player::MoveLeft, this), CommandManager::InputCommands::moveLeft);
		CommandManager::GetInstance().AddCallBack(std::bind(&Player::MoveRight, this), CommandManager::InputCommands::moveRight);
		CommandManager::GetInstance().AddCallBack(std::bind(&Player::Pump, this), CommandManager::InputCommands::pump);
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		AddComponent(std::make_shared<TransformComponent>());

		auto spriteWalking = std::make_shared<SpriteComponent>("../Resources/Character/DigDug/Walk.png", 0.0f, 0.0f, 27.0f, 14.0f, 2, 1, 8);
		auto spriteDigging = std::make_shared<SpriteComponent>("../Resources/Character/DigDug/Dig.png", 0.0f, 0.0f, 29.0f, 14.0f, 2, 1, 6);
		auto playerCollision = std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(3.0f, 3.0f, 12.0f, 12.0f));

		m_pSprites.push_back(spriteWalking);
		m_pSprites.push_back(spriteDigging);
		SetSpritesInvisible();
		m_pSprites[static_cast<int>(PlayerSprites::walking)]->SetVisibility(true);


		GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });

		AddComponent(spriteWalking);
		AddComponent(spriteDigging);
		AddComponent(playerCollision);

		GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Player::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));


		m_DigDug.GetBlackboard().m_pPlayer = weak_from_this();
		m_DigDug.Initialize();
	}

	void Player::OnOverlap(std::shared_ptr<CollisionComponent> playerCollision, std::shared_ptr<CollisionComponent> otherCollision)
	{

		if (std::shared_ptr<Tunnel> tunnel = std::dynamic_pointer_cast<Tunnel>(otherCollision->GetGameObject()))
		{
			m_DigDug.GetBlackboard().m_IsDigging = true;
			tunnel->GetComponent<TextureComponent>()->SetVisibility(true);
		}
		else
		{
			m_DigDug.GetBlackboard().m_IsDigging = false;
		}


	}

	std::shared_ptr<SpriteComponent> Player::GetPlayerSprites(PlayerSprites playerSprites)
	{
		return m_pSprites[static_cast<int>(playerSprites)];
	}

	void Player::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
		m_DigDug.Update();
		m_ElapsedSec += deltaTime;

		Vector2f currPos = GetComponent<TransformComponent>()->GetPosition();
		Vector2f velocity = m_DigDug.GetBlackboard().m_Velocity;

		GetComponent<TransformComponent>()->SetPosition(velocity + currPos);
		m_DigDug.GetBlackboard().m_Velocity = Vector2f{ 0,0 };
		m_IsButtonPressed = false;
	}

	void Player::Draw() const
	{
		GameObject::Draw();
	}

	void Player::SetSpritesInvisible()
	{
		for (int i = 0; i < m_pSprites.size(); i++)
		{
			m_pSprites[i]->SetVisibility(false);
		}
	}

	void Player::MoveLeft()
	{
		if (!m_IsButtonPressed)
		{
			m_DigDug.GetBlackboard().m_Velocity.x = -m_Speed * Timing::GetInstance().GetDeltaTime();
			m_IsButtonPressed = true;
		}
	}

	void Player::MoveRight()
	{
		if (!m_IsButtonPressed)
		{
			m_DigDug.GetBlackboard().m_Velocity.x = m_Speed * Timing::GetInstance().GetDeltaTime();
			m_IsButtonPressed = true;
		}
	}

	void Player::MoveUp()
	{
		if (!m_IsButtonPressed)
		{
			m_DigDug.GetBlackboard().m_Velocity.y = -m_Speed * Timing::GetInstance().GetDeltaTime();
			m_IsButtonPressed = true;
		}
	}

	void Player::MoveDown()
	{
		if (!m_IsButtonPressed)
		{
			m_DigDug.GetBlackboard().m_Velocity.y = m_Speed * Timing::GetInstance().GetDeltaTime();
			m_IsButtonPressed = true;
		}
	}

	void Player::Pump()
	{
		m_ElapsedSec = 0.0f;


		if (m_ElapsedSec >= 1.0f)
		{
			if (--m_Pump > 0)
			{
				m_DigDug.GetBlackboard().m_IsPumping = false;
			}
			m_ElapsedSec = 0.0f;
		}

		m_DigDug.GetBlackboard().m_IsPumping = true;
		++m_Pump;


		switch (m_Pump)
		{
		case 0:
			std::cout << "THREW THE PUMP\n";
			break;
		case 1:
			std::cout << "Pump phase 01\n";
			break;
		case 2:
			std::cout << "Pump phase 02\n";
			break;
		case 3:
			std::cout << "Pump phase 02\n";
			break;
		}
	}
}