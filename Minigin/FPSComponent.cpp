#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextDrawComponent.h"
#include "GameObject.h"

namespace cem
{
	FPSComponent::FPSComponent()
		:m_FPS()
	{
	}

	float FPSComponent::GetFPS() const
	{
		return m_FPS;
	}

	void FPSComponent::Update(float deltaTime)
	{
		m_FPS = 1.0f / deltaTime;

		std::shared_ptr<GameObject> go = m_pGameObject.lock();
		if (go)
		{
			auto txtComponent = go->GetComponent<TextDrawComponent>();
			if (txtComponent)
			{
				go->GetComponent<TextDrawComponent>()->SetText("FPS: " + std::to_string(int(m_FPS)));
			}
			else
			{
				std::cout << "No TextDrawComponent found!\n";
			}
		}
	}

	void FPSComponent::Draw() const
	{
	}

}