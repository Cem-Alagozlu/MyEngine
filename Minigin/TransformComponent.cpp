#include "MiniginPCH.h"
#include "TransformComponent.h"



TransformComponent::TransformComponent()
	:m_PositionformObject{ 0.0f,0.0f }
	,m_ScaleObject{1.0f,1.0f}
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

//Be careful that you don't achieve the pitfalls associated 
//with inheritance in your component system (which is designed to avoid those).
//Consider only using inheritance on components with a strict "is a" relationship, 
//the FPS component calculates the fps and USES the functionality of a text component 
//to draw it. It has a completely different purpose than a component that draws text. 
//You could use two components and have the FPS component set the text of the TextDrawComponent.