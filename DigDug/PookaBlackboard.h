#pragma once
#include "Blackboard.h"
#include "Structs.h"

class GameObject;
class PookaBlackboard final : public Blackboard
{
public:
	PookaBlackboard();
	~PookaBlackboard();

	Vector2f m_Velocity;
};

