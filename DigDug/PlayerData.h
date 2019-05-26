#pragma once
#include "Singleton.h"

namespace cem
{
	class PlayerData final : public Singleton<PlayerData>
	{
	public:
		enum class PlayerAchievements : int
		{
			digAchievement = 0,
			dugAchievement = 1,
			deadAchievement = 2,
			fruityAchievement = 3,
			Count = 4
		};
	
		void Initialize();
		~PlayerData() = default;

		void AddLives(int life);
		int GetLives();

		void AddScore(int score);
		int GetScore();

		void SetGameOver(bool endGame);
		bool GetGameOver();

		void SetAchievement(PlayerAchievements achievement,bool hasAchievement);
		bool GetAchievements(PlayerAchievements achievement);

	private:
		int m_Lives;
		int m_Score;
		bool m_IsGameOver;

		std::vector<bool> m_Achievements;
	};
}

