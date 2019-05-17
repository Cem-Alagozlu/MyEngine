#include "DigDugPCH.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "CommandManager.h"
#include "Timing.h"
#include "CollisionComponent.h"
#include "PhysicsManager.h"


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
	m_pSprites.push_back(spriteWalking);
	GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });
	AddComponent(spriteWalking);
	AddComponent(std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic,Rectf(0.0f, 0.0f,14.0f,14.0f)));
	GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Player::OnOverlap, this,std::placeholders::_1,std::placeholders::_2));


	m_DigDug.GetBlackboard().m_pPlayer = weak_from_this();
	m_DigDug.Initialize();
}

void Player::OnOverlap(std::shared_ptr<CollisionComponent> playerCollision, std::shared_ptr<CollisionComponent> otherCollision)
{
	std::cout << "Collision \n";
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	m_DigDug.Update();

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
	std::cout << "Move right \n";
}

void Player::MoveUp()
{
	if (!m_IsButtonPressed)
	{
		m_DigDug.GetBlackboard().m_Velocity.y = -m_Speed * Timing::GetInstance().GetDeltaTime();
		m_IsButtonPressed = true;
	}
	std::cout << "Move up \n";
}

void Player::MoveDown()
{ 
	if (!m_IsButtonPressed)
	{
		m_DigDug.GetBlackboard().m_Velocity.y = m_Speed * Timing::GetInstance().GetDeltaTime();
		m_IsButtonPressed = true;
	}
	std::cout << "Move down \n";
}

void Player::Pump()
{
	std::cout << "Pump\n";
}
