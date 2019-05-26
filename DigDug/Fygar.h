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
			fire = 2
		
		};

		enum class FygarTextures : int
		{
			blowUpPhase01 = 0,
			blowUpPhase02 = 1,
			blowUpPhase03 = 2
		};

		Fygar();
		~Fygar();

		void Initialize(std::shared_ptr<World> pWorld, std::shared_ptr<Player> pPlayer);
		void OnOverlap(std::shared_ptr<CollisionComponent> fygarCollision, std::shared_ptr<CollisionComponent> otherCollision);
		std::shared_ptr<SpriteComponent> GetFygarSprites(FygarSprites fygarSprites);
		std::shared_ptr<TextureComponent> GetFygarBlowUpTextures(FygarTextures fygarTextures);

		void SetSpritesInvisible();
		void SetTexturesInvisible();
		bool GettingPumped();
		void SetGettingPumped(bool isPumped);
		bool IsDead();
		void SetDead(bool isDead);

	protected:
		virtual void Update(float deltaTime) override;
		void Draw() const;
	private:
		FygarStateMachine m_Fygar;
		bool m_IsDead;
		std::vector<std::shared_ptr<SpriteComponent>> m_pSprites;
		std::vector<std::shared_ptr<TextureComponent>> m_pTextures;
		Vector2f m_TargetPos;
		const int m_BlowUpIMG{ 3 };
		std::weak_ptr<World> m_pWorld;
		std::weak_ptr<Player> m_pPlayer;
		float m_Speed;
	
	};
}
