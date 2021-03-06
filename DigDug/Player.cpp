#include "DigDugPCH.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "CommandManager.h"
#include "Timing.h"
#include "CollisionComponent.h"
#include "Tunnel.h"
#include "PlayerHUD.h"
#include "PlayerData.h"
#include "PickUpFruit.h"
#include "Achievements.h"
#include "Pooka.h"
#include "Fygar.h"

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
		auto spriteDigging = std::make_shared<SpriteComponent>("../Resources/Character/DigDug/Dig.png", 0.0f, 0.0f, 29.0f, 14.0f, 2, 1, 8);
		auto spritePumping = std::make_shared<SpriteComponent>("../Resources/Character/DigDug/Pump.png", 0.0f, 0.0f, 80.0f, 15.0f, 2, 1, 8);
		auto spriteDead = std::make_shared<SpriteComponent>("../Resources/Character/DigDug/Dead.png", 0.0f, 0.0f, 64.0f, 16.0f, 3, 1, 8);
		auto playerCollision = std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(0.0f, 0.0f, 25.0f, 25.0f));

		m_pSprites.push_back(spriteWalking);
		m_pSprites.push_back(spriteDigging);
		m_pSprites.push_back(spritePumping);
		m_pSprites.push_back(spriteDead);
		SetSpritesInvisible();
		m_pSprites[static_cast<int>(PlayerSprites::walking)]->SetVisibility(true);


		GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });

		AddComponent(spriteWalking);
		AddComponent(spriteDigging);
		AddComponent(spritePumping);
		AddComponent(spriteDead);
		AddComponent(playerCollision);

		GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Player::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));

		m_DigDug.GetBlackboard().m_IsPumping = false;
		m_DigDug.GetBlackboard().m_IsPumpingEnemy = false;
		m_DigDug.GetBlackboard().m_pPlayer = weak_from_this();
		m_DigDug.Initialize();

		Achievements::GetInstance().Initialize(std::dynamic_pointer_cast<Player>(shared_from_this()));
		PlayerData::GetInstance().Initialize();
	}

	void Player::OnOverlap(std::shared_ptr<CollisionComponent> playerCollision, std::shared_ptr<CollisionComponent> otherCollision)
	{

		if (std::shared_ptr<Tunnel> tunnel = std::dynamic_pointer_cast<Tunnel>(otherCollision->GetGameObject()))
		{
			if (!tunnel->GetComponent<TextureComponent>()->GetVisibility())
			{
				m_DigDug.GetBlackboard().m_IsDigging = true;
				m_pObserver->OnNotify(Events::playerDig);
				m_pObserver->OnNotify(Events::playerDug);
				PlayerData::GetInstance().AddScore(5);
				tunnel->GetComponent<TextureComponent>()->SetVisibility(true);
			}
		}

		if (std::shared_ptr<Pooka> pooka = std::dynamic_pointer_cast<Pooka>(otherCollision->GetGameObject()))
		{
			if (m_DigDug.GetBlackboard().m_IsPumping)
			{
				m_DigDug.GetBlackboard().m_pEnemy = pooka;
				m_DigDug.GetBlackboard().m_IsPumpingEnemy = true;
			}
		}

		if (std::shared_ptr<Fygar> fygar = std::dynamic_pointer_cast<Fygar>(otherCollision->GetGameObject()))
		{
			if (m_DigDug.GetBlackboard().m_IsPumping)
			{
				m_DigDug.GetBlackboard().m_pEnemy = fygar;
				m_DigDug.GetBlackboard().m_IsPumpingEnemy = true;
			}
		}

	}

	std::shared_ptr<SpriteComponent> Player::GetPlayerSprites(PlayerSprites playerSprites)
	{
		return m_pSprites[static_cast<int>(playerSprites)];
	}

	void Player::Update(float deltaTime)
	{
		if (!PlayerData::GetInstance().GetGameOver())
		{


			GameObject::Update(deltaTime);
			m_DigDug.Update();
			m_ElapsedSec += deltaTime;

			Vector2f currPos = GetComponent<TransformComponent>()->GetPosition();
			Vector2f velocity = m_DigDug.GetBlackboard().m_Velocity;


			if (currPos.x > 422.0f)
			{
				currPos.x = 422.0f;
			}

			if (currPos.x < 0.0f)
			{
				currPos.x = 0.0f;
			}

			if (currPos.y <= 25.0f)
			{
				currPos.y = 25.0f;
			}
			if (currPos.y >= 666.6f)
			{
				currPos.y = 666.6f;
			}


			GetComponent<TransformComponent>()->SetPosition(velocity + currPos);
			m_DigDug.GetBlackboard().m_Velocity = Vector2f{ 0,0 };
			m_IsButtonPressed = false;


			if (PlayerData::GetInstance().GetLives() <= 0)
			{
				PlayerData::GetInstance().SetGameOver(true);
				SetSpritesInvisible();
			}
		}

	}

	void Player::Draw() const
	{
		GameObject::Draw();
	}

	void Player::SetSpritesInvisible()
	{
		for (size_t i = 0; i < m_pSprites.size(); i++)
		{
			m_pSprites[i]->SetVisibility(false);
		}
	}

	bool Player::IsPlayerPumping()
	{
		return m_DigDug.GetBlackboard().m_IsPumping;
	}

	bool Player::IsPlayerPumpingEnemy(std::shared_ptr<GameObject> pEnemy)
	{
		if (m_DigDug.GetBlackboard().m_pEnemy.lock() == pEnemy)
		{
			return m_DigDug.GetBlackboard().m_IsPumpingEnemy;
		}
		return false;
	}

	void Player::SetEnemyPumped(bool enemyPumped)
	{
		m_DigDug.GetBlackboard().m_IsPumpingEnemy = enemyPumped;
	}

	void Player::SetObserver(Observer* pObserver)
	{
		m_pObserver = pObserver;
	}

	Observer* Player::GetPlayerObserver()
	{
		return m_pObserver;
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
		m_DigDug.GetBlackboard().m_IsPumping = true;
	}
}
