#pragma once
#include "DigDugStateMachine.h"
#include "SpriteComponent.h"
#include "GameObject.h"

class Player final : public GameObject
{
public:
	Player();
	~Player();

	void Initialize();

	

protected:
	virtual void Update(float deltaTime) override;
	void Draw() const;

private:
	DigDugStateMachine m_DigDug;
	std::vector<std::shared_ptr<SpriteComponent>> m_pSprites;

	float m_Speed;
	bool m_IsButtonPressed;
	bool m_HasSpearThrown;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Pump();
};

