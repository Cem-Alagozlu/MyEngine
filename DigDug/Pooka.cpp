#include "DigDugPCH.h"
#include "Pooka.h"
#include "Tunnel.h"
#include "Timing.h"
#include "PlayerData.h"

namespace cem
{

	Pooka::Pooka()
	{
	}


	Pooka::~Pooka()
	{
	}

	void Pooka::Initialize(std::shared_ptr<World> pWorld, std::shared_ptr<Player> pPlayer)
	{
		m_pWorld = pWorld;
		m_pPlayer = pPlayer;
		AddComponent(std::make_shared<TransformComponent>());

		auto spriteWalking = std::make_shared<SpriteComponent>("../Resources/Character/Pooka/Walk.png", 0.0f, 0.0f, 30.0f, 14.0f, 2, 1, 2);
		auto spriteTeleporting = std::make_shared<SpriteComponent>("../Resources/Character/Pooka/Teleport.png", 0.0f, 0.0f, 30.0f, 8.0f, 2, 1, 2);
		auto pookaCollision = std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(3.0f, 3.0f, 12.0f, 12.0f));

		m_pSprites.push_back(spriteWalking);
		m_pSprites.push_back(spriteTeleporting);
		m_pSprites[static_cast<int>(PookaSprites::walking)]->SetVisibility(true);

		GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });

		AddComponent(spriteTeleporting);
		AddComponent(spriteWalking);
		AddComponent(pookaCollision);

		GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Pooka::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));

		spriteTeleporting->SetVisibility(false);
		m_Pooka.GetBlackboard().m_pPooka = weak_from_this();
		m_Pooka.Initialize();
		m_Pooka.GetBlackboard().m_Speed = 2.0f;
	}

	void Pooka::OnOverlap(std::shared_ptr<CollisionComponent> pookaCollision, std::shared_ptr<CollisionComponent> otherCollision)
	{
		std::shared_ptr<Tunnel> tunnel = std::dynamic_pointer_cast<Tunnel>(otherCollision->GetGameObject());

		if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(otherCollision->GetGameObject()))
		{
			if (player->IsPlayerPumping())
			{
				std::cout << "ye boi\n";
			}
			else
			{
				PlayerData::GetInstance().SetLives(-1);
				player->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 0.0f,0.0f });
			}
		}

	}


	std::shared_ptr<SpriteComponent> Pooka::GetPookaSprites(PookaSprites pookaSprites)
	{
		return m_pSprites[static_cast<int>(pookaSprites)];
	}

	void Pooka::SetSpritesInvisible()
	{
		for (int i = 0; i < m_pSprites.size(); i++)
		{
			m_pSprites[i]->SetVisibility(false);
		}
	}


	void Pooka::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
		m_Pooka.Update();

		Vector2f currPos = GetComponent<TransformComponent>()->GetPosition();
		Vector2f normalizeVec{};

		m_TargetPos = m_pWorld.lock()->GetTarget(m_pPlayer.lock(), shared_from_this());
		normalizeVec = m_TargetPos - currPos;
		Normalize(normalizeVec);
		normalizeVec = normalizeVec * Timing::GetInstance().GetDeltaTime() * m_Pooka.GetBlackboard().m_Speed;
		GetComponent<TransformComponent>()->SetPosition(normalizeVec + currPos);

	}

	void Pooka::Draw() const
	{
		GameObject::Draw();
	}
}
