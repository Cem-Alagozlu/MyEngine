#pragma once
#include "GameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "PookaStateMachine.h"
#include "World.h"

namespace cem
{
	class Pooka final : public GameObject
	{
	public:
		enum class PookaSprites : int
		{
			walking = 0,
			teleporting = 1,
			crushed = 2,
			blowup = 3
		};

		enum class PookaTextures : int
		{
			blowUpPhase01 = 0,
			blowUpPhase02 = 1,
			blowUpPhase03 = 2
		};

		Pooka();
		~Pooka();

		void Initialize(std::shared_ptr<World> pWorld, std::shared_ptr<Player> pPlayer);
		void OnOverlap(std::shared_ptr<CollisionComponent> pookaCollision, std::shared_ptr<CollisionComponent> otherCollision);
		std::shared_ptr<SpriteComponent> GetPookaSprites(PookaSprites pookaSprites);
		std::shared_ptr<TextureComponent> GetPookaBlowUpTextures(PookaTextures pookaTextures);

		void SetSpritesInvisible();
		void SetTexturesInvisible();
		bool GettingPumped();
		void SetGettingPumped(bool isPumped);


	protected:
		virtual void Update(float deltaTime) override;
		void Draw() const;

	private:
		PookaStateMachine m_Pooka;
		std::vector<std::shared_ptr<SpriteComponent>> m_pSprites;
		std::vector<std::shared_ptr<TextureComponent>> m_pTextures;
		const int m_BlowUpIMG{ 3 };
		Vector2f m_TargetPos;
		std::weak_ptr<World> m_pWorld;
		std::weak_ptr<Player> m_pPlayer;
		float m_Speed;
	};
}

