#pragma once
#include "Singleton.h"
#include "CollisionComponent.h"

/*
	 * physics manager -> singleton -> update : alle collision compon uit scene !*/

class PhysicsManager : public Singleton<PhysicsManager>
{
public:
	PhysicsManager();
	~PhysicsManager();

	void AddComponent(std::shared_ptr<CollisionComponent> collisionComponent);
	void Update();


private:
	std::vector<std::shared_ptr<CollisionComponent>> m_pCollisionComponents;
};
