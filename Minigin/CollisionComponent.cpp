#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "PhysicsManager.h"
#include "GameObject.h"

CollisionComponent::CollisionComponent(CollisionType type, const Rectf& collisionRect)
	:m_CollisionType(type)
	,m_CollisionRect{collisionRect}
{

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

bool CollisionComponent::IsOverlapping(std::shared_ptr<CollisionComponent> otherComp)
{
	auto getInfo = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	auto getInfoOther = otherComp->GetGameObject()->GetComponent<TransformComponent>()->GetPosition();

	if (GetGameObject())
	{
		Rectf newCollisionRect = m_CollisionRect;
		Rectf newOtherCollisionRect = otherComp->m_CollisionRect;

		newCollisionRect.left += getInfo.x;
		newCollisionRect.bottom += getInfo.y;

		newOtherCollisionRect.left += getInfoOther.x;
		newOtherCollisionRect.bottom += getInfoOther.y;

		return IsOverlapping(newCollisionRect, newOtherCollisionRect);
	}
	return false;
}

void CollisionComponent::AddCallBack(std::function<void(std::shared_ptr<CollisionComponent>, std::shared_ptr<CollisionComponent>)> callBack)
{
	m_Functions.push_back(callBack);
}


const std::vector<CollisionComponent::CollisionCallBack>& CollisionComponent::GetCallBacks()
{
	return m_Functions;
}

void CollisionComponent::SetCollisionType(CollisionType type)
{
	m_CollisionType = type;
}

CollisionComponent::CollisionType CollisionComponent::GetCollisionType()
{
	return m_CollisionType;
}

void CollisionComponent::Update(float /*deltaTime*/)
{
}

void CollisionComponent::Draw() const
{
}
