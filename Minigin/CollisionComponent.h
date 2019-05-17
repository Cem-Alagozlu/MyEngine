#pragma once
#include "BaseComponent.h"
#include "Structs.h"

class CollisionComponent final : public BaseComponent
{
public:
	using CollisionCallBack = std::function<void(std::shared_ptr<CollisionComponent>, std::shared_ptr<CollisionComponent>)>;
	enum class CollisionType : uint8_t
	{
		Dynamic,
		Static
	};


	CollisionComponent(CollisionType type, const Rectf& collisionRect);
	virtual ~CollisionComponent() = default;


	bool IsOverlapping(std::shared_ptr<CollisionComponent> otherComp);
	void AddCallBack(CollisionCallBack callBack);
	const std::vector<CollisionCallBack>& GetCallBacks();
	void SetCollisionType(CollisionType type);
	CollisionType GetCollisionType();

protected:
	void Update(float deltaTime) override;
	void Draw() const override;

private:
	std::vector<CollisionCallBack> m_Functions;
	bool IsOverlapping(const Rectf& r1, const Rectf& r2);
	Rectf m_CollisionRect;
	CollisionType m_CollisionType;
};
 
//constexpr int a = sizeof(CollisionComponent::CollisionCallBack);