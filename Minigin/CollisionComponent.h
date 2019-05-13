#pragma once
#include "BaseComponent.h"
#include "Structs.h"

class CollisionComponent final : public BaseComponent
{
public:
	enum class CollisionType
	{
		Dynamic,
		Static
	};


	CollisionComponent();
	virtual ~CollisionComponent() = default;

	bool IsOverlapping(const Rectf& r1, const Rectf& r2);
	void AddCallBack(std::function<void(std::shared_ptr<CollisionComponent>, std::shared_ptr<CollisionComponent>)> callBack);


protected:
	void Update(float deltaTime) override;
	void Draw() const override;

private:
	std::vector<std::function<void(std::shared_ptr<CollisionComponent>, std::shared_ptr<CollisionComponent>)>> m_Functions;
	Rectf m_CollisionRect;
	CollisionType m_CollisionType;
};
