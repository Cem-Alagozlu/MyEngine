#include "MiniginPCH.h"
#include "BaseComponent.h"

namespace cem
{
	BaseComponent::BaseComponent()
	{
	}

	std::shared_ptr<GameObject> BaseComponent::GetGameObject()
	{
		return m_pGameObject.lock();
	}
}
