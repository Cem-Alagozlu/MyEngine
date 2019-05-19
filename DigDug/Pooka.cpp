#include "DigDugPCH.h"
#include "Pooka.h"
#include "Tunnel.h"


Pooka::Pooka()
{
}


Pooka::~Pooka()
{
}

void Pooka::Initialize()
{
	AddComponent(std::make_shared<TransformComponent>());

	auto spriteWalking = std::make_shared<SpriteComponent>("../Resources/Character/Pooka/Walk.png", 0.0f, 0.0f, 30.0f, 14.0f, 2, 1, 6);

	m_pSprites.push_back(spriteWalking);
	m_pSprites[static_cast<int>(PookaSprites::walking)]->SetVisibility(true);

	GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Pooka::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));

	m_Pooka.GetBlackboard().m_pPooka = weak_from_this();
	m_Pooka.Initialize();
}

void Pooka::OnOverlap(std::shared_ptr<CollisionComponent> pookaCollision,std::shared_ptr<CollisionComponent> otherCollision)
{
	std::shared_ptr<Tunnel> tunnel = std::dynamic_pointer_cast<Tunnel>(otherCollision->GetGameObject());


}


std::shared_ptr<SpriteComponent> Pooka::GetPookaSprites(PookaSprites pookaSprites)
{
	return m_pSprites[static_cast<int>(pookaSprites)];
}

void Pooka::SetSpritesInvisible()
{
}

void Pooka::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	m_Pooka.Update();
}

void Pooka::Draw() const
{
	GameObject::Draw();
}
