#pragma once
#include "State.h"

namespace cem
{
	class FygarStateTeleport  final : public State
	{
	public:
		FygarStateTeleport();
		virtual ~FygarStateTeleport();
	protected:
		void Enter() override;
		void Exit() override;
		void Update() override;
		bool CanTransition() override;
	};
}
