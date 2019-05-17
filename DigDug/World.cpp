#include "DigDugPCH.h"
#include "World.h"
#include "TextureComponent.h"
#include "Tunnel.h"
#include "CollisionComponent.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "TextDrawComponent.h"


World::World()
	:m_CellDistance(32)
{
}


World::~World()
{
}

void World::Initialize(Scene& scene)
{
	AddComponent(std::make_shared<TransformComponent>());
	AddComponent(std::make_shared<TextureComponent>("../Resources/Level/bgLevel.png"));
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 14;j ++)
		{
			auto tunnel = std::make_shared<Tunnel>();
			tunnel->Initialize();
			tunnel->GetComponent<TransformComponent>()->SetPosition(Vector2f{ float(j * m_CellDistance), float(i * m_CellDistance) + 60 });
			m_pTunnels.push_back(tunnel);
			scene.AddChild(tunnel);
		}			
	}
}

void World::OnOverlap(std::shared_ptr<CollisionComponent> playerComponent, std::shared_ptr<CollisionComponent> otherComponent)
{	
	auto it = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
		[otherComponent](std::shared_ptr<Tunnel>& tunnel) 
	{return tunnel->GetComponent<CollisionComponent>() == otherComponent; });


	if (playerComponent == m_pPlayer->GetComponent<CollisionComponent>() && it != m_pTunnels.end())
	{
		//(*it)-> set visibility
	}

}

void World::SetPlayer(std::shared_ptr<Player> player)
{
	m_pPlayer = player;
}


void World::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void World::Draw() const
{
	GameObject::Draw();
}
