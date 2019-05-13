#pragma once
#include "GameObject.h"
#include "Tunnel.h"
#include "CollisionComponent.h"
#include "Player.h"

class Scene;

class World final : public GameObject
{
public:
	World();
	~World();

	void Initialize(Scene& scene);
	void OnOverlap(std::shared_ptr<CollisionComponent> playerComponent, std::shared_ptr<CollisionComponent> otherComponent);
	void SetPlayer(std::shared_ptr<Player> player);


protected:
	virtual void Update(float deltaTime) override;
	virtual void Draw() const override;

private:
	const float m_CellDistance;
	std::vector<std::shared_ptr<Tunnel>> m_pTunnels;
	std::shared_ptr<Player> m_pPlayer;
};

