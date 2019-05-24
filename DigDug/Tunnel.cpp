#include "DigDugPCH.h"
#include "Tunnel.h"
#include "CollisionComponent.h"
namespace cem
{

	void Tunnel::Initialize()
	{
		AddComponent(std::make_shared<TransformComponent>());
		auto textureComp = std::make_shared<TextureComponent>("../Resources/Level/tunnel.png");
		textureComp->SetVisibility(false);
		AddComponent(textureComp);
		AddComponent(std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Static, Rectf(0.0f, 0.0f, 28.0f, 28.0f)));
	}


	void Tunnel::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
	}

	void Tunnel::Draw() const
	{
		GameObject::Draw();
	}

}