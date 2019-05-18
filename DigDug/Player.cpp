#include "DigDugPCH.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "CommandManager.h"
#include "Timing.h"
#include "CollisionComponent.h"
#include "Tunnel.h"


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
	auto spriteDigging = std::make_shared<SpriteComponent>("../Resources/Character/DigDug/Dig.png", 0.0f, 0.0f, 29.0f, 14.0f,2,1,8);
	auto playerCollision = std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(0.0f, 0.0f, 14.0f, 14.0f));

	m_pSprites.push_back(spriteWalking);
	m_pSprites.push_back(spriteDigging);
	SetSpritesInvisible();
	

	GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });

	AddComponent(spriteWalking);
	AddComponent(spriteDigging);
	AddComponent(playerCollision);

	GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Player::OnOverlap, this,std::placeholders::_1,std::placeholders::_2));


	m_DigDug.GetBlackboard().m_pPlayer = weak_from_this();
	m_DigDug.Initialize();
}

void Player::OnOverlap(std::shared_ptr<CollisionComponent> playerCollision, std::shared_ptr<CollisionComponent> otherCollision)
{

	if (std::shared_ptr<Tunnel> tunnel = std::dynamic_pointer_cast<Tunnel>(otherCollision->GetGameObject()))
	{
		if (!tunnel->GetComponent<TextureComponent>()->GetVisibility())
		{
			m_DigDug.GetBlackboard().m_IsDigging = false;
		}

		m_DigDug.GetBlackboard().m_IsDigging = true;
		tunnel->GetComponent<TextureComponent>()->SetVisibility(true);
		

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

	Vector2f currPos = GetComponent<TransformComponent>()->GetPosition();
	Vector2f velocity = m_DigDug.GetBlackboard().m_Velocity;

	GetComponent<TransformComponent>()->SetPosition(velocity + currPos);
	m_DigDug.GetBlackboard().m_Velocity = Vector2f{ 0,0 };
	m_IsButtonPressed = false;
	m_DigDug.GetBlackboard().m_IsDigging = false;

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
