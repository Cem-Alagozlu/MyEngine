#pragma once
#include "State.h"

class DigDugStatePump final : public State
{
public:
	DigDugStatePump() = default;
	~DigDugStatePump();

protected:
	void Enter() override;
	void Exit() override;
	void Update() override;
	bool CanTransition() override;

};

