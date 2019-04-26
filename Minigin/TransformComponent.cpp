#include "MiniginPCH.h"
#include "TransformComponent.h"



TransformComponent::TransformComponent()
	:m_TransformObject{ 0.0f,0.0f }
{
}

Vector2f TransformComponent::GetPosition() const
{
	return m_TransformObject;
}

void TransformComponent::SetPosition(Vector2f pos)
{
	m_TransformObject = pos;
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