#pragma once
#include "GameObject.h"
#include "CollisionComponent.h"

namespace cem
{
	class PickUpFruit final : public GameObject
	{
	public:
		PickUpFruit() = default;
		~PickUpFruit() = default;

		void Initialize();
		void SetScoreFromFruit();
		void Respawn();
		void OnOverlap(std::shared_ptr<CollisionComponent> fruitCollision, std::shared_ptr<CollisionComponent> otherCollision);

	protected:
		virtual void Update(float deltaTime) override;
		virtual void Draw() const override;

	private:
		const int m_TotalFruits{ 11 };
		int m_RandomFruitSelector;
		float m_RandomSpawnerTime;
		Vector2f m_MoveOut;
		Vector2f m_RandomPos;
		std::vector<std::shared_ptr<GameObject>> m_pFruits;
	};
}

