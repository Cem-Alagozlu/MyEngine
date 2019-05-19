#pragma once
#include "Blackboard.h"
#include "Structs.h"

class GameObject;
class PookaBlackboard final : public Blackboard
{
public:
	PookaBlackboard();
	~PookaBlackboard();



	std::weak_ptr<GameObject> m_pPooka;
	Vector2f m_Velocity;
};

