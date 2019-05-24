#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Player.h"
#include "World.h"
#include "FygarStateMachine.h"

namespace cem
{
	class Fygar final : public GameObject
	{
	public:
		enum class FygarSprites : int
		{
			walking = 0,
			teleporting = 1,
			crushed = 2,
			blowup = 3,
			fire = 4
		};

		Fygar();
		~Fygar();

		void Initialize(std::shared_ptr<World> pWorld, std::shared_ptr<Player> pPlayer);
		void OnOverlap(std::shared_ptr<CollisionComponent> fygarCollision, std::shared_ptr<CollisionComponent> otherCollision);
		std::shared_ptr<SpriteComponent> GetFygarSprites(FygarSprites fygarSprites);

		void SetSpritesInvisible();
	protected:
		virtual void Update(float deltaTime) override;
		void Draw() const;
	private:
		FygarStateMachine m_Fygar;
		std::vector<std::shared_ptr<SpriteComponent>> m_pSprites;
		Vector2f m_TargetPos;
		std::weak_ptr<World> m_pWorld;
		std::weak_ptr<Player> m_pPlayer;
		float m_Speed;

	};
}
