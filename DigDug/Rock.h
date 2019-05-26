#pragma once
#include "GameObject.h"
#include "World.h"

namespace cem
{
	class Rock final : public GameObject
	{
	public:
		Rock(std::shared_ptr<World> pWorld);
		~Rock() = default;

		void OnOverlap(std::shared_ptr<CollisionComponent> rockCollision, std::shared_ptr<CollisionComponent> otherCollision);

		void Initialize();

	protected:
		virtual void Update(float deltaTime) override;
		virtual void Draw() const override;

	private:
		std::shared_ptr<GameObject> m_pRock;
		std::weak_ptr<World> m_pWorld;
		Vector2f m_TargetPos;
		bool m_UnstoppableForceOfDOOM;
	};
}

