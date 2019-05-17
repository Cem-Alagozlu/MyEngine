#include "MiniginPCH.h"
#include "BaseComponent.h"

BaseComponent::BaseComponent()
{
}

std::shared_ptr<GameObject> BaseComponent::GetGameObject()
{
	return m_pGameObject.lock();
}
