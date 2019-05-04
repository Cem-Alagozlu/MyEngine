#pragma once
#include "State.h"

class DigDugStateIdle final : public State
{
public:
	DigDugStateIdle() = default;
	virtual ~DigDugStateIdle();

protected:
	void Enter() override;
	void Exit() override;
	void Update() override;
	bool CanTransition() override;
};



