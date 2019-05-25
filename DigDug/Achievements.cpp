#include "DigDugPCH.h"
#include "Achievements.h"

namespace cem
{
	void Achievements::Initialize(std::shared_ptr<Player> pPlayer)
	{
		pPlayer->SetObserver(this);
	}
	void Achievements::OnNotify(Events event)
	{
		switch (event)
		{
		case Events::playerDig:
			++m_TotalDigs;
			if (m_TotalDigs == 10 && !m_HasPlayerDigAchievement)
			{
				std::cout << "ya boi has dig achievement" << std::endl;
				m_HasPlayerDigAchievement = true;
			}
			break;
		case Events::playerDug:
			++m_TotalDugs;
			break;
		case Events::playerDead:
			++m_TotalDeaths;
			break;
		}
	}
}