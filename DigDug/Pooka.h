#pragma once
#include "GameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

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
	void OnOverlap(std::shared_ptr<CollisionComponent> playerCollision, std::shared_ptr<CollisionComponent> otherCollision);
	std::shared_ptr<SpriteComponent> GetPookaSprites(PookaSprites playerSprites);
	void SetSpritesInvisible();

protected:
	virtual void Update(float deltaTime) override;
	void Draw() const;

	float m_Speed;
};

