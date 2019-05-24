#pragma once
#include "State.h"

namespace cem
{
	class FygarStateMove final : public State
	{
	public:
		FygarStateMove();
		virtual ~FygarStateMove();
	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;
	};
}

