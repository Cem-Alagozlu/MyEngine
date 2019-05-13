#include "DigDugPCH.h"
#include "Tunnel.h"
#include "CollisionComponent.h"

void Tunnel::Initialize()
{
	AddComponent(std::make_shared<TextureComponent>("../Resources/Level/tunnel.png"));
	AddComponent(std::make_shared<TransformComponent>());
	//AddComponent(std::make_shared<CollisionComponent>())
}

void Tunnel::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Tunnel::Draw() const
{
	GameObject::Draw();
}
