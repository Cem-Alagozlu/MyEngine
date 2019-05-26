#pragma once
#include "State.h"

namespace cem
{
	class FygarStatePumped final : public State

	{
	public:
		FygarStatePumped();
		virtual~FygarStatePumped();
	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;

	};
}
