#include "DigDugPCH.h"
#include "PookaStateTeleport.h"
#include "DigDugBlackboard.h"
#include "PookaBlackboard.h"


PookaStateTeleport::PookaStateTeleport()
{
}


PookaStateTeleport::~PookaStateTeleport()
{
}

void PookaStateTeleport::Enter()
{

}

void PookaStateTeleport::Exit()
{
}

void PookaStateTeleport::Update()
{

	//random timer 10 - 15
	//aftellen
	// if 0 , transition teleport state 
	// reset back

}

bool PookaStateTeleport::CanTransition()
{
	bool isTeleporting = GetBlackboard<PookaBlackboard>()->m_IsTeleporting;

	if (isTeleporting)
	{
		return true;
	}
	return false;
}
