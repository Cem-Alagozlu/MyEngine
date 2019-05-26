#include "DigDugPCH.h"
#include "Fygar.h"
#include "Timing.h"
#include "PlayerData.h"
#include "Rock.h"
#include "ThreadManager.h"

namespace cem
{
	Fygar::Fygar()
	{
	}


	Fygar::~Fygar()
	{
	}

	void Fygar::Initialize(std::shared_ptr<World> pWorld, std::shared_ptr<Player> pPlayer)
	{
		m_pWorld = pWorld;
		m_pPlayer = pPlayer;
		m_IsDead = false;
		AddComponent(std::make_shared<TransformComponent>());

		auto spriteWalking = std::make_shared<SpriteComponent>("../Resources/Character/Fygar/Walk.png", 0.0f, 0.0f, 28.0f, 13.0f, 2, 1, 2);
		auto spriteTeleporting = std::make_shared<SpriteComponent>("../Resources/Character/Fygar/Teleport.png", 0.0f, 0.0f, 29.0f, 11.0f, 2, 1, 2);
		auto spriteFiring = std::make_shared<SpriteComponent>("../Resources/Character/Fygar/Fire00.png", 0.0f, 0.0f, 90.0f, 16.0f, 2, 1, 2);
		auto fygarCollision = std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(3.0f, 3.0f, 12.0f, 12.0f));

		auto blowUpPhase01 = std::make_shared<TextureComponent>("../Resources/Character/Fygar/phase01.png");
		auto blowUpPhase02 = std::make_shared<TextureComponent>("../Resources/Character/Fygar/phase02.png");
		auto blowUpPhase03 = std::make_shared<TextureComponent>("../Resources/Character/Fygar/phase03.png");
		blowUpPhase01->SetVisibility(false);
		blowUpPhase01->SetVisibility(false);
		blowUpPhase01->SetVisibility(false);

		m_pTextures.push_back(blowUpPhase01);
		m_pTextures.push_back(blowUpPhase02);
		m_pTextures.push_back(blowUpPhase03);

		m_pSprites.push_back(spriteWalking);
		m_pSprites.push_back(spriteTeleporting);
		m_pSprites.push_back(spriteFiring);
		m_pSprites[static_cast<int>(FygarSprites::walking)]->SetVisibility(true);

		GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });

		AddComponent(blowUpPhase01);
		AddComponent(blowUpPhase02);
		AddComponent(blowUpPhase03);

		AddComponent(spriteTeleporting);
		AddComponent(spriteWalking);
		AddComponent(spriteFiring);
		AddComponent(fygarCollision);

		GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Fygar::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));

		SetTexturesInvisible();
		spriteTeleporting->SetVisibility(false);


		m_Fygar.GetBlackboard().m_pFygar = weak_from_this();
		m_Fygar.Initialize();
		m_Fygar.GetBlackboard().m_Speed = 2.0f;
		m_Fygar.GetBlackboard().m_PumpPhase = 0;

	}

	void Fygar::OnOverlap(std::shared_ptr<CollisionComponent> fygarCollision,
		std::shared_ptr<CollisionComponent> otherCollision)
	{
		if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(otherCollision->GetGameObject()))
		{
			if (player->IsPlayerPumping())
			{
				m_Fygar.GetBlackboard().m_PumpedTimer += 0.5f;
				SetSpritesInvisible();
			}
			else
			{
				if (!m_Fygar.GetBlackboard().m_IsBeingPumped)
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

	std::shared_ptr<SpriteComponent> Fygar::GetFygarSprites(FygarSprites fygarSprites)
	{
		return m_pSprites[static_cast<int>(fygarSprites)];
	}

	std::shared_ptr<TextureComponent> Fygar::GetFygarBlowUpTextures(FygarTextures fygarTextures)
	{
		return m_pTextures[static_cast<int>(fygarTextures)];
	}

	void Fygar::SetSpritesInvisible()
	{
		for (size_t i = 0; i < m_pSprites.size(); i++)
		{
			m_pSprites[i]->SetVisibility(false);
		}
	}

	void Fygar::SetTexturesInvisible()
	{
		for (size_t i = 0; i < m_pTextures.size(); i++)
		{
			m_pTextures[i]->SetVisibility(false);
		}
	}

	bool Fygar::GettingPumped()
	{
		return m_pPlayer.lock()->IsPlayerPumpingEnemy(shared_from_this());
	}

	void Fygar::SetGettingPumped(bool isPumped)
	{
		m_pPlayer.lock()->SetEnemyPumped(isPumped);
	}

	bool Fygar::IsDead()
	{

		return m_IsDead;
	}

	void Fygar::SetDead(bool isDead)
	{
		m_IsDead = isDead;
	}

	void Fygar::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
		ThreadManager::GetInstance().GetEnemyThread().AddTask([this]()
		{

		m_Fygar.Update();

		Vector2f currPos = GetComponent<TransformComponent>()->GetPosition();
		Vector2f normalizeVec{};

		m_TargetPos = m_pWorld.lock()->GetTarget(m_pPlayer.lock(), shared_from_this());
		normalizeVec = m_TargetPos - currPos;
		Normalize(normalizeVec);
		normalizeVec = normalizeVec * Timing::GetInstance().GetDeltaTime() * m_Fygar.GetBlackboard().m_Speed;
		GetComponent<TransformComponent>()->SetPosition(normalizeVec + currPos);
		});
	}

	void Fygar::Draw() const
	{
		GameObject::Draw();
	}
}
