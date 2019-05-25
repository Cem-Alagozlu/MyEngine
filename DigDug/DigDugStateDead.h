#pragma once
#include "State.h"

namespace cem
{
	class DigDugStateDead : public State
	{
	public:
		DigDugStateDead();
		virtual ~DigDugStateDead();

	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;
	};
}

