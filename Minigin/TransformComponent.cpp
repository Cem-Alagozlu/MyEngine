#include "MiniginPCH.h"
#include "TransformComponent.h"

namespace cem
{
	TransformComponent::TransformComponent()
		:m_PositionformObject{ 0.0f,0.0f }
		, m_ScaleObject{ 1.0f,1.0f }
	{
	}

	Vector2f TransformComponent::GetPosition() const
	{
		return m_PositionformObject;
	}

	void TransformComponent::SetPosition(Vector2f pos)
	{
		m_PositionformObject = pos;
	}

	Vector2f TransformComponent::GetScale() const
	{
		return m_ScaleObject;
	}

	void TransformComponent::SetScale(Vector2f scale)
	{
		m_ScaleObject = scale;
	}


	void TransformComponent::Update(float /*deltaTime*/)
	{

	}

	void TransformComponent::Draw() const
	{

	}

}
