#pragma once
#include "GameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "PookaStateMachine.h"

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

	void Initialize();
	void OnOverlap(std::shared_ptr<CollisionComponent> pookaCollision, std::shared_ptr<CollisionComponent> otherCollision);
	std::shared_ptr<SpriteComponent> GetPookaSprites(PookaSprites pookaSprites);

	void SetSpritesInvisible();

protected:
	virtual void Update(float deltaTime) override;
	void Draw() const;

private:
	PookaStateMachine m_Pooka;
	std::vector<std::shared_ptr<SpriteComponent>> m_pSprites;

	float m_Speed;
};

