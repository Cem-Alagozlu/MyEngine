#include "MiniginPCH.h"
#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
	:m_CollisionType(CollisionType::Static)
{
	/*
	 * collision type constructor meegeven , rectf ook meegeven
	 * physics manager -> singleton -> update : alle collision compon uit scene !
	 * check every comp with each other
	 * then if overlap = true , callback , van coll & call die functie 
	 * met collision components
	 */
}

bool CollisionComponent::IsOverlapping(const Rectf & r1, const Rectf & r2)
{
	// If one rectangle is on left side of the other
	if (r1.left + r1.width < r2.left || r2.left + r2.width < r1.left)
	{
		return false;
	}

	// If one rectangle is under the other
	if (r1.bottom > r2.bottom + r2.height || r2.bottom > r1.bottom + r1.height)
	{
		return false;
	}

	return true;
}

void CollisionComponent::AddCallBack(std::function<void(std::shared_ptr<CollisionComponent>, std::shared_ptr<CollisionComponent>)> callBack)
{
	m_Functions.push_back(callBack);
}

void CollisionComponent::Update(float /*deltaTime*/)
{
}

void CollisionComponent::Draw() const
{
}
