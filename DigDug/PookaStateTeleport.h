#pragma once
#include "State.h"

class PookaStateTeleport final : public State
{
public:
	PookaStateTeleport();
	virtual ~PookaStateTeleport();

protected:
	void Enter() override;
	void Exit() override;
	void Update() override;
	bool CanTransition() override;
};

