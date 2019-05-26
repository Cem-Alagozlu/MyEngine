#include "DigDugPCH.h"
#include "Pooka.h"
#include "Tunnel.h"
#include "Timing.h"
#include "PlayerData.h"
#include "ThreadManager.h"
#include "Rock.h"

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
		m_IsDead = false;
		m_Pooka.GetBlackboard().m_IsBeingPumped = false;
		AddComponent(std::make_shared<TransformComponent>());

		auto spriteWalking = std::make_shared<SpriteComponent>("../Resources/Character/Pooka/Walk.png", 0.0f, 0.0f, 30.0f, 14.0f, 2, 1, 2);
		auto spriteTeleporting = std::make_shared<SpriteComponent>("../Resources/Character/Pooka/Teleport.png", 0.0f, 0.0f, 30.0f, 8.0f, 2, 1, 2);
		auto pookaCollision = std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(3.0f, 3.0f, 12.0f, 12.0f));



		auto blowUpPhase01 = std::make_shared<TextureComponent>("../Resources/Character/Pooka/phase01.png");
		auto blowUpPhase02 = std::make_shared<TextureComponent>("../Resources/Character/Pooka/phase02.png");
		auto blowUpPhase03 = std::make_shared<TextureComponent>("../Resources/Character/Pooka/phase03.png");
		blowUpPhase01->SetVisibility(false);
		blowUpPhase01->SetVisibility(false);
		blowUpPhase01->SetVisibility(false);

		m_pTextures.push_back(blowUpPhase01);
		m_pTextures.push_back(blowUpPhase02);
		m_pTextures.push_back(blowUpPhase03);

		m_pSprites.push_back(spriteWalking);
		m_pSprites.push_back(spriteTeleporting);
		m_pSprites[static_cast<int>(PookaSprites::walking)]->SetVisibility(true);

		GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });

		AddComponent(blowUpPhase01);
		AddComponent(blowUpPhase02);
		AddComponent(blowUpPhase03);

		AddComponent(spriteTeleporting);
		AddComponent(spriteWalking);
		AddComponent(pookaCollision);

		GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Pooka::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));

		spriteTeleporting->SetVisibility(false);
		SetTexturesInvisible();

		m_Pooka.GetBlackboard().m_pPooka = weak_from_this();
		m_Pooka.Initialize();
		m_Pooka.GetBlackboard().m_Speed = 2.0f;
		m_Pooka.GetBlackboard().m_PumpPhase = 0;
	}

	void Pooka::OnOverlap(std::shared_ptr<CollisionComponent> pookaCollision, std::shared_ptr<CollisionComponent> otherCollision)
	{
		
		if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(otherCollision->GetGameObject()))
		{
			if (player->IsPlayerPumping())
			{
				m_Pooka.GetBlackboard().m_PumpedTimer += 0.5f;
				SetSpritesInvisible();
			}
			else
			{
				if (!m_Pooka.GetBlackboard().m_IsBeingPumped)
				{
					m_pPlayer.lock()->GetPlayerObserver()->OnNotify(Events::playerDead);
					PlayerData::GetInstance().AddLives(-1);
					player->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 0.0f,0.0f });
				}
			}
		}


		if (std::shared_ptr<Rock> rock = std::dynamic_pointer_cast<Rock>(otherCollision->GetGameObject()))
		{
			m_IsDead = true;
		}

	}


	std::shared_ptr<SpriteComponent> Pooka::GetPookaSprites(PookaSprites pookaSprites)
	{
		return m_pSprites[static_cast<int>(pookaSprites)];
	}

	std::shared_ptr<TextureComponent> Pooka::GetPookaBlowUpTextures(PookaTextures pookaTextures)
	{
		return m_pTextures[static_cast<int>(pookaTextures)];
	}

	void Pooka::SetSpritesInvisible()
	{
		for (int i = 0; i < m_pSprites.size(); i++)
		{
			m_pSprites[i]->SetVisibility(false);
		}
	}

	void Pooka::SetTexturesInvisible()
	{
		for (int i = 0; i < m_pTextures.size(); i++)
		{
			m_pTextures[i]->SetVisibility(false);
		}
	}

	bool Pooka::GettingPumped()
	{
		return m_pPlayer.lock()->IsPlayerPumpingEnemy(shared_from_this());
	}

	void Pooka::SetGettingPumped(bool isPumped)
	{
		m_pPlayer.lock()->SetEnemyPumped(isPumped);
	}

	bool Pooka::IsDead()
	{
		return m_IsDead;
	}

	void Pooka::SetDead(bool isDead)
	{
		m_IsDead = isDead;
	}


	void Pooka::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
		
			ThreadManager::GetInstance().GetEnemyThread().AddTask([this]()
			{

				m_Pooka.Update();
				Vector2f currPos = GetComponent<TransformComponent>()->GetPosition();
				Vector2f normalizeVec{};

				m_TargetPos = m_pWorld.lock()->GetTarget(m_pPlayer.lock(), shared_from_this());
				normalizeVec = m_TargetPos - currPos;
				Normalize(normalizeVec);
				normalizeVec = normalizeVec * Timing::GetInstance().GetDeltaTime() * m_Pooka.GetBlackboard().m_Speed;
				GetComponent<TransformComponent>()->SetPosition(normalizeVec + currPos);
			});

	}

	void Pooka::Draw() const
	{
		GameObject::Draw();
	}
}
