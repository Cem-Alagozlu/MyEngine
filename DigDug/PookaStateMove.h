#pragma once
#include "State.h"


class PookaStateMove final : public State
{
public:
	PookaStateMove();
	virtual ~PookaStateMove();

protected:
	void Enter() override;
	void Exit() override;
	void Update() override;
	bool CanTransition() override;
};

