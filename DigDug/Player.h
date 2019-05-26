#pragma once
#include "DigDugStateMachine.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Observer.h"


namespace cem
{
	class Player final : public GameObject
	{
	public:
		enum class Event
		{
			dig,
			dug,
			died
		};
		enum class PlayerSprites : int
		{
			walking = 0,
			digging = 1,
			pumping = 2,
			dead = 3
		};

		Player();
		~Player();

		void Initialize();
		void OnOverlap(std::shared_ptr<CollisionComponent> playerCollision, std::shared_ptr<CollisionComponent> otherCollision);
		std::shared_ptr<SpriteComponent> GetPlayerSprites(PlayerSprites playerSprites);
		void SetSpritesInvisible();
		bool IsPlayerPumping();
		bool IsPlayerPumpingEnemy(std::shared_ptr<GameObject> pEnemy);
		void SetEnemyPumped(bool enemyPumped);

		void SetObserver(Observer* pObserver);
		Observer* GetPlayerObserver();
	protected:
		virtual void Update(float deltaTime) override;
		void Draw() const;

	private:
		DigDugStateMachine m_DigDug;
		std::vector<std::shared_ptr<cem::SpriteComponent>> m_pSprites;
		Observer* m_pObserver;

		float m_Speed;
		bool m_IsButtonPressed;
		bool m_HasSpearThrown;
		int m_Pump;
		float m_ElapsedSec;

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
		void Pump();
	};
}
