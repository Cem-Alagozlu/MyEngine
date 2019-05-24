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

	private:
		int m_Lives;
		int m_Score;
	};
}

