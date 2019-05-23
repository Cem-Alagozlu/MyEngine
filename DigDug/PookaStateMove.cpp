#include "DigDugPCH.h"
#include "PookaStateMove.h"
#include "Timing.h"
#include "PookaBlackboard.h"


PookaStateMove::PookaStateMove()
{
}


PookaStateMove::~PookaStateMove()
{
}

void PookaStateMove::Enter()
{
}

void PookaStateMove::Exit()
{
}

void PookaStateMove::Update()
{
	//generate rand//
	//bool check, change if ; 
	// tunnel check weg

	float teleportTimer = rand() % 15 + 10;

	teleportTimer -= Timing::GetInstance().GetDeltaTime();

	if (teleportTimer >= 0.0f)
	{
		GetBlackboard<PookaBlackboard>()->m_IsTeleporting = true;
	}
}

bool PookaStateMove::CanTransition()
{
	return true;
}
