#pragma once
#include "State.h"

namespace cem
{
	class DigDugStateDig final : public State
	{
	public:
		DigDugStateDig();
		virtual ~DigDugStateDig();

	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;
	};
}

