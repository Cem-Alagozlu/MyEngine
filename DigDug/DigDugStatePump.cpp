#include "DigDugPCH.h"
#include "DigDugStatePump.h"
#include "DigDugBlackboard.h"

namespace cem
{
	DigDugStatePump::~DigDugStatePump()
	{
	}

	void DigDugStatePump::Enter()
	{
	}

	void DigDugStatePump::Exit()
	{
	}

	void DigDugStatePump::Update()
	{
	}

	bool DigDugStatePump::CanTransition()
	{
		bool isPumping = GetBlackboard<DigDugBlackboard>()->m_IsPumping;

		if (isPumping)
		{
			return true;
		}

		return false;
	}
}
