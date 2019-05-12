#pragma once
#include "BaseComponent.h"
#include "Structs.h"

class CollisionComponent final : public BaseComponent
{
public:
	CollisionComponent();
	virtual ~CollisionComponent() = default;

	bool IsOverlapping(const Rectf& r1, const Rectf& r2);

protected:
	void Update(float deltaTime) override;
	void Draw() const override;
};
