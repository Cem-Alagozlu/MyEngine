#pragma once
#include "GameObject.h"
#include "Tunnel.h"
#include "CollisionComponent.h"
#include "Player.h"
#include <array>

namespace cem
{
	class Scene;

	struct NeighbouringTiles
	{
		std::array<std::shared_ptr<Tunnel>, 4> tunnels;

		enum Direction
		{
			left,
			right,
			up,
			down
		};

		std::shared_ptr<Tunnel> operator[](Direction dir)
		{
			return tunnels[dir];
		}

		void Set(Direction dir, std::shared_ptr<Tunnel> pTunnel)
		{
			tunnels[dir] = pTunnel;
		}

	};

	class World final : public GameObject
	{
	public:

		World();
		~World();

		void Initialize(Scene& scene);
		void OnOverlap(std::shared_ptr<CollisionComponent> playerComponent, std::shared_ptr<CollisionComponent> otherComponent);
		void SetPlayer(std::shared_ptr<Player> player);
		NeighbouringTiles GetNeighbours(std::shared_ptr<Tunnel> tunnel);
		Vector2f GetTarget(std::shared_ptr<Player> player, std::shared_ptr<GameObject> enemy);

		std::vector<std::shared_ptr<Tunnel>> GetTunnels();

	protected:
		virtual void Update(float deltaTime) override;
		virtual void Draw() const override;

	private:
		const float m_CellDistance;
		std::vector<std::shared_ptr<Tunnel>> m_pTunnels;
		std::shared_ptr<Player> m_pPlayer;
	};
}
