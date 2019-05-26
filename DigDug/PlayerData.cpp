#include "DigDugPCH.h"
#include "PlayerData.h"

namespace cem
{
	void PlayerData::Initialize()
	{
		m_Lives = 3;
		m_Score = 0;

		for (int i = 0; i <static_cast<int>(PlayerAchievements::Count); i++)
		{
			m_Achievements.push_back(false);
		}
	}


	int PlayerData::GetLives()
	{	
		return m_Lives;
	}


	void PlayerData::AddLives(int life)
	{
		m_Lives += life;
	}

	int PlayerData::GetScore()
	{
		return m_Score;
	}

	void PlayerData::SetGameOver(bool endGame)
	{
		m_IsGameOver = endGame;
	}

	bool PlayerData::GetGameOver()
	{
		return m_IsGameOver;
	}

	void PlayerData::SetAchievement(PlayerAchievements achievement, bool hasAchievement)
	{
		m_Achievements[static_cast<int>(achievement)] = hasAchievement;
	}

	bool PlayerData::GetAchievements(PlayerAchievements achievement)
	{
		return m_Achievements[static_cast<int>(achievement)];
	}

	void PlayerData::AddScore(int score)
	{
		m_Score += score;
	}
}