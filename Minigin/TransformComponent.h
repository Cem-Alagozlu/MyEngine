#pragma once
#include "Structs.h"
#include "BaseComponent.h"

namespace cem
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		virtual ~TransformComponent() = default;

		Vector2f GetPosition() const;
		void SetPosition(Vector2f pos);

		Vector2f GetScale() const;
		void SetScale(Vector2f scale);

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
	protected:

		void Update(float deltaTime) override;
		void Draw() const override;

	private:
		Vector2f m_PositionformObject;
		Vector2f m_ScaleObject;
	};
}

