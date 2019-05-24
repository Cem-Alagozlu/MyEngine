#pragma once
#include "State.h"

namespace cem
{
	class DigDugStateMove final : public State
	{
	public:
		DigDugStateMove();
		virtual ~DigDugStateMove();

	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;
	};
}