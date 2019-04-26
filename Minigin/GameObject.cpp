#include "MiniginPCH.h"
#include "GameObject.h"

GameObject::~GameObject()
{
}

void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
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