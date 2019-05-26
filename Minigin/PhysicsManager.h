#pragma once
#include "Singleton.h"
#include "CollisionComponent.h"

/*
	 * physics manager -> singleton -> update : alle collision compon uit scene !*/

namespace cem
{
	class PhysicsManager : public Singleton<PhysicsManager>
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		void AddComponent(std::shared_ptr<CollisionComponent> collisionComponent);
		void RemoveComponent(std::shared_ptr<CollisionComponent> collisionComponent);
		void Update();


	private:
		std::vector<std::shared_ptr<CollisionComponent>> m_pCollisionComponents;
	};
}