#pragma once
#include "State.h"

namespace cem
{
	class PookaStatePumped final : public State
	{
	public:
		PookaStatePumped();
		virtual~PookaStatePumped();

	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;
	};
}
