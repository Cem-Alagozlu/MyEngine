#pragma once
#include "Blackboard.h"
#include "Structs.h"

class GameObject;
class DigDugBlackboard final : public Blackboard
{
public:
	DigDugBlackboard();
	~DigDugBlackboard();


	Vector2f m_Velocity;
	bool m_IsDigging;
	bool m_IsPumping;
	std::weak_ptr<GameObject> m_pPlayer;
};

