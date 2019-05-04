#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

class ColliderComponent final : public BaseComponent
{
public:
	ColliderComponent();
	~ColliderComponent();

protected:
	void Update(float deltaTime) override;
	void Draw() const override;

private:
	SDL_Rect m_Collider;
	std::string m_Tag;
};

