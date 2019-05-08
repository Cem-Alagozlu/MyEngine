#pragma once
#include "Blackboard.h"

class DigDugBlackboard final : public Blackboard
{
public:
	DigDugBlackboard();
	~DigDugBlackboard();

	int TotalSteps{5};

};

