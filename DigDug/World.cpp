#include "DigDugPCH.h"
#include "World.h"
#include "TextureComponent.h"
#include "Tunnel.h"
#include "CollisionComponent.h"
#include "Scene.h"
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
	//auto it = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
	//	[otherComponent](std::shared_ptr<Tunnel>& tunnel) 
	//{return tunnel->GetComponent<CollisionComponent>() == otherComponent; });

}

void World::SetPlayer(std::shared_ptr<Player> player)
{
	m_pPlayer = player;
}

NeighbouringTiles World::GetNeighbours(std::shared_ptr<Tunnel> tunnel)
{
	auto tunnelPos = tunnel->GetComponent<TransformComponent>()->GetPosition();
	NeighbouringTiles neighbourTiles{};

	auto itLeft = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
		[tunnelPos](std::shared_ptr<Tunnel> otherTunnel)
	{
		Vector2f newTunnelPos = Vector2f{tunnelPos.x - 32.0f, tunnelPos.y};
		if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
		{
			return true;
		}
	});


	auto itRight = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
		[tunnelPos](std::shared_ptr<Tunnel> otherTunnel)
	{
		Vector2f newTunnelPos = Vector2f{ tunnelPos.x + 32.0f, tunnelPos.y };
		if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
		{
			return true;
		}
	});

	auto itUp = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
		[tunnelPos](std::shared_ptr<Tunnel> otherTunnel)
	{
		Vector2f newTunnelPos = Vector2f{ tunnelPos.x , tunnelPos.y - 32.0f };
		if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
		{
			return true;
		}
	});

	auto itDown = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
		[tunnelPos](std::shared_ptr<Tunnel> otherTunnel)
	{
		Vector2f newTunnelPos = Vector2f{ tunnelPos.x , tunnelPos.y + 32.0f };
		if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
		{
			return true;
		}
	});


	neighbourTiles[NeighbouringTiles::left] = *itLeft;
	neighbourTiles[NeighbouringTiles::right] = *itRight;
	neighbourTiles[NeighbouringTiles::up ]= *itUp;
	neighbourTiles[NeighbouringTiles::down] = *itDown;

	//pos asignen
	//update van enemy naar targetpos
	// if on target pos, check opnieuw, ( welke tile next is )
	return neighbourTiles;
}

std::shared_ptr<Tunnel> World::GetTarget(std::shared_ptr<Player> player, std::shared_ptr<GameObject> enemy,
	NeighbouringTiles& neighbours)
{
	auto posPlayer = player->GetComponent<TransformComponent>()->GetPosition();
	float distanceLeft{}, distanceRight{}, distanceUp{}, distanceDown{};

	float currMinDistance = std::numeric_limits<float>::max();
	std::shared_ptr<Tunnel> currClosestTunnel;


	for (int i = 0; i < neighbours.tunnels.size(); i++)
	{
		if (neighbours.tunnels[i]->GetComponent<SpriteComponent>()->GetVisibility())
		{
			float distance = Distance(player->GetComponent<TransformComponent>()->GetPosition(), neighbours.tunnels[i]->GetComponent<TransformComponent>()->GetPosition());

			if (distance < currMinDistance)
			{
				currMinDistance = distance;
				currClosestTunnel = neighbours.tunnels[i];
			}
		}
	}
	return currClosestTunnel;
}


void World::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void World::Draw() const
{
	GameObject::Draw();
}
