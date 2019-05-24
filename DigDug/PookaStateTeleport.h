#pragma once
#include "State.h"

namespace cem
{
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
}

