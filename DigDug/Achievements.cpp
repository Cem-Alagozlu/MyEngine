#include "DigDugPCH.h"
#include "Achievements.h"
#include "PlayerHUD.h"
#include "PlayerData.h"

namespace cem
{
	void Achievements::Initialize(std::shared_ptr<Player> pPlayer)
	{
		pPlayer->SetObserver(this);
	}
	void Achievements::OnNotify(Events event)
	{
		auto achievementDig = PlayerData::GetInstance().GetAchievements(PlayerData::PlayerAchievements::digAchievement);
		auto achievementDug = PlayerData::GetInstance().GetAchievements(PlayerData::PlayerAchievements::dugAchievement);
		auto achievementDead = PlayerData::GetInstance().GetAchievements(PlayerData::PlayerAchievements::deadAchievement);
		auto achievementFruity = PlayerData::GetInstance().GetAchievements(PlayerData::PlayerAchievements::fruityAchievement);

		switch (event)
		{
		case Events::playerDig:
			++m_TotalDigs;
			if (m_TotalDigs == 20  && !achievementDig)
			{
				PlayerData::GetInstance().SetAchievement(PlayerData::PlayerAchievements::digAchievement, true);
			}
			break;
		case Events::playerDug:
			++m_TotalDugs;
			if (m_TotalDugs == 40 && !achievementDug)
			{
				PlayerData::GetInstance().SetAchievement(PlayerData::PlayerAchievements::dugAchievement, true);
			}
			break;
		case Events::playerDead:
			++m_TotalDeaths;
			if (m_TotalDeaths == 2 && !achievementDead)
			{
				PlayerData::GetInstance().SetAchievement(PlayerData::PlayerAchievements::deadAchievement, true);
			}
			break;
		case Events::playerFruity:
			++m_TotalFruits;
			if (m_TotalFruits == 5 && !achievementFruity)
			{
				PlayerData::GetInstance().SetAchievement(PlayerData::PlayerAchievements::fruityAchievement, true);
			}
			break;
		}
	}
}
