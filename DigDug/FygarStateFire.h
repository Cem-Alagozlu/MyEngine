#pragma once
#include "State.h"

namespace cem
{
	class FygarStateFire final : public State
	{
	public:
		FygarStateFire();
		virtual~FygarStateFire();
	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;
	};
}

