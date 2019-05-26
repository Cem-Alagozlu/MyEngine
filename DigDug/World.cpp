#include "DigDugPCH.h"
#include "World.h"
#include "TextureComponent.h"
#include "Tunnel.h"
#include "CollisionComponent.h"
#include "Scene.h"
#include "TextDrawComponent.h"

namespace cem
{

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
			for (int j = 0; j < 14; j++)
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
			Vector2f newTunnelPos = Vector2f{ tunnelPos.x - 32.0f, tunnelPos.y };
			if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
			{
				return true;
			}
			return false;
		});


		auto itRight = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
			[tunnelPos](std::shared_ptr<Tunnel> otherTunnel)
		{
			Vector2f newTunnelPos = Vector2f{ tunnelPos.x + 32.0f, tunnelPos.y };
			if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
			{
				return true;
			}
			return false;
		});

		auto itUp = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
			[tunnelPos](std::shared_ptr<Tunnel> otherTunnel)
		{
			Vector2f newTunnelPos = Vector2f{ tunnelPos.x , tunnelPos.y - 32.0f };
			if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
			{
				return true;
			}
			return false;
		});

		auto itDown = std::find_if(m_pTunnels.begin(), m_pTunnels.end(),
			[tunnelPos](std::shared_ptr<Tunnel> otherTunnel)
		{
			Vector2f newTunnelPos = Vector2f{ tunnelPos.x , tunnelPos.y + 32.0f };
			if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
			{
				return true;
			}
			return false;
		});

		if (itDown != m_pTunnels.end())
		{
			neighbourTiles.Set(NeighbouringTiles::down, *itDown);
		}
		if (itUp != m_pTunnels.end())
		{
			neighbourTiles.Set(NeighbouringTiles::up, *itUp);
		}
		if (itRight != m_pTunnels.end())
		{

			neighbourTiles.Set(NeighbouringTiles::right, *itRight);
		}
		if (itLeft != m_pTunnels.end())
		{
			neighbourTiles.Set(NeighbouringTiles::left, *itLeft);
		}
		return neighbourTiles;
	}

	Vector2f World::GetTarget(std::shared_ptr<Player> player, std::shared_ptr<GameObject> enemy)
	{
		Vector2f pos = enemy->GetComponent<TransformComponent>()->GetPosition();

		auto it = std::min_element(m_pTunnels.begin(), m_pTunnels.end(),
			[pos](std::shared_ptr<Tunnel> pTunnel01, std::shared_ptr<Tunnel> pTunnel02)
		{
			float tunnelDistance01 = Distance(pos, pTunnel01->GetComponent<TransformComponent>()->GetPosition());
			float tunnelDistance02 = Distance(pos, pTunnel02->GetComponent<TransformComponent>()->GetPosition());

			return tunnelDistance01 < tunnelDistance02;
		});


		NeighbouringTiles tiles = GetNeighbours(*it);


		auto posPlayer = player->GetComponent<TransformComponent>()->GetPosition();
		float currMinDistance = std::numeric_limits<float>::max();
		std::shared_ptr<Tunnel> currClosestTunnel;


		for (size_t i = 0; i < tiles.tunnels.size(); i++)
		{
			if (!tiles.tunnels[i])
			{
				continue;
			}
			if (tiles.tunnels[i]->GetComponent<TextureComponent>()->GetVisibility())
			{
				float distance = Distance(player->GetComponent<TransformComponent>()->GetPosition(), tiles.tunnels[i]->GetComponent<TransformComponent>()->GetPosition());

				if (distance < currMinDistance)
				{
					currMinDistance = distance;
					currClosestTunnel = tiles.tunnels[i];
				}
			}
		}
		if (!currClosestTunnel)
		{
			return player->GetComponent<TransformComponent>()->GetPosition();
		}
		return currClosestTunnel->GetComponent<TransformComponent>()->GetPosition();
	}

	std::vector<std::shared_ptr<Tunnel>> World::GetTunnels()
	{
		return m_pTunnels;
	}


	void World::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
	}

	void World::Draw() const
	{
		GameObject::Draw();
	}
}