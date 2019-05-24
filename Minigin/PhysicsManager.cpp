#include "MiniginPCH.h"
#include "PhysicsManager.h"


namespace cem
{
	PhysicsManager::PhysicsManager()
	{
	}


	PhysicsManager::~PhysicsManager()
	{
	}

	void PhysicsManager::AddComponent(std::shared_ptr<CollisionComponent> collisionComponent)
	{
		m_pCollisionComponents.push_back(collisionComponent);
	}

	void PhysicsManager::Update()
	{
		for (size_t i = 0; i < m_pCollisionComponents.size(); i++)
		{
			for (size_t j = 0; j < m_pCollisionComponents.size(); j++)
			{
				if (i == j)
				{
					continue;
				}
				if (m_pCollisionComponents[i]->GetCollisionType() == CollisionComponent::CollisionType::Static
					&&
					m_pCollisionComponents[j]->GetCollisionType() == CollisionComponent::CollisionType::Static
					)
				{
					continue;
				}
				if (m_pCollisionComponents[i]->IsOverlapping(m_pCollisionComponents[j]))
				{
					for (CollisionComponent::CollisionCallBack compCall : m_pCollisionComponents[i]->GetCallBacks())
					{
						compCall(m_pCollisionComponents[i], m_pCollisionComponents[j]);
					}
				}
			}
		}
	}

}