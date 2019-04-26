#pragma once
#include "Structs.h"
#include "BaseComponent.h"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;

	Vector2f GetPosition() const;
	void SetPosition(Vector2f pos);


	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) noexcept = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
protected:

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	Vector2f m_TransformObject;
};

