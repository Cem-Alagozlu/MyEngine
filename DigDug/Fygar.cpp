#include "DigDugPCH.h"
#include "Fygar.h"
#include "Timing.h"

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
		AddComponent(std::make_shared<TransformComponent>());

		auto spriteWalking = std::make_shared<SpriteComponent>("../Resources/Character/Fygar/Walk.png", 0.0f, 0.0f, 28.0f, 13.0f, 2, 1, 2);
		auto spriteTeleporting = std::make_shared<SpriteComponent>("../Resources/Character/Fygar/Teleport.png", 0.0f, 0.0f, 29.0f, 11.0f, 2, 1, 2);
		auto fygarCollision = std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(3.0f, 3.0f, 12.0f, 12.0f));

		m_pSprites.push_back(spriteWalking);
		m_pSprites.push_back(spriteTeleporting);
		m_pSprites[static_cast<int>(FygarSprites::walking)]->SetVisibility(true);

		GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,2.3f });

		AddComponent(spriteTeleporting);
		AddComponent(spriteWalking);
		AddComponent(fygarCollision);

		GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Fygar::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));


		spriteTeleporting->SetVisibility(false);
		m_Fygar.GetBlackboard().m_pFygar = weak_from_this();
		m_Fygar.Initialize();
		m_Fygar.GetBlackboard().m_Speed = 2.0f;
	}

	void Fygar::OnOverlap(std::shared_ptr<CollisionComponent> fygarCollision,
		std::shared_ptr<CollisionComponent> otherCollision)
	{
		std::shared_ptr<Tunnel> tunnel = std::dynamic_pointer_cast<Tunnel>(otherCollision->GetGameObject());
	}

	std::shared_ptr<SpriteComponent> Fygar::GetFygarSprites(FygarSprites fygarSprites)
	{
		return m_pSprites[static_cast<int>(fygarSprites)];
	}

	void Fygar::SetSpritesInvisible()
	{
		for (int i = 0; i < m_pSprites.size(); i++)
		{
			m_pSprites[i]->SetVisibility(false);
		}
	}

	void Fygar::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
		m_Fygar.Update();

		Vector2f currPos = GetComponent<TransformComponent>()->GetPosition();
		Vector2f normalizeVec{};

		m_TargetPos = m_pWorld.lock()->GetTarget(m_pPlayer.lock(), shared_from_this());
		normalizeVec = m_TargetPos - currPos;
		Normalize(normalizeVec);
		normalizeVec = normalizeVec * Timing::GetInstance().GetDeltaTime() * m_Fygar.GetBlackboard().m_Speed;
		GetComponent<TransformComponent>()->SetPosition(normalizeVec + currPos);
	}

	void Fygar::Draw() const
	{
		GameObject::Draw();
	}
}
