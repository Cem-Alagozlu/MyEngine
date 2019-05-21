#pragma once
#include "GameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "PookaStateMachine.h"
#include "World.h"

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

	Pooka();
	~Pooka();

	void Initialize(std::shared_ptr<World> pWorld,std::shared_ptr<Player> pPlayer);
	void OnOverlap(std::shared_ptr<CollisionComponent> pookaCollision, std::shared_ptr<CollisionComponent> otherCollision);
	std::shared_ptr<SpriteComponent> GetPookaSprites(PookaSprites pookaSprites);

	void SetSpritesInvisible();

protected:
	virtual void Update(float deltaTime) override;
	void Draw() const;

private:
	PookaStateMachine m_Pooka;
	std::vector<std::shared_ptr<SpriteComponent>> m_pSprites;
	Vector2f m_TargetPos;
	std::weak_ptr<World> m_pWorld;
	std::weak_ptr<Player> m_pPlayer;
	float m_Speed;
};

