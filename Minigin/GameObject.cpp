#include "MiniginPCH.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "PhysicsManager.h"

GameObject::~GameObject()
{
}

void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
	std::shared_ptr<CollisionComponent> collComp = std::dynamic_pointer_cast<CollisionComponent>(component);
	if (collComp)
	{
		PhysicsManager::GetInstance().AddComponent(collComp);
	}
	component->m_pGameObject = shared_from_this();
}

void GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Update(deltaTime);
	}
}

void GameObject::Draw() const
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Draw();
	}
}