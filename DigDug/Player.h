#pragma once
#include "DigDugStateMachine.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"

class Player final : public GameObject
{
public:
	enum class PlayerSprites : int
	{
		walking = 0,
		digging = 1
	};

	Player();
	~Player();

	void Initialize();
	void OnOverlap(std::shared_ptr<CollisionComponent> playerCollision, std::shared_ptr<CollisionComponent> otherCollision);
	std::shared_ptr<SpriteComponent> GetPlayerSprites(PlayerSprites playerSprites);
	void SetSpritesInvisible();

protected:
	virtual void Update(float deltaTime) override;
	void Draw() const;

private:
	DigDugStateMachine m_DigDug;
	std::vector<std::shared_ptr<SpriteComponent>> m_pSprites;



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

