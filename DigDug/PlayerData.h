#pragma once
#include "Singleton.h"

namespace cem
{
	class PlayerData final : public Singleton<PlayerData>
	{
	public:
		void Initialize();
		~PlayerData() = default;

		void SetLives(int life);
		int GetLives();

		void SetScore(int score);
		int GetScore();

		void SetGameOver(bool endGame);
		bool GetGameOver();

	private:
		int m_Lives;
		int m_Score;
		bool m_IsGameOver;
	};
}

