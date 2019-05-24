#include "DigDugPCH.h"
#include "PlayerData.h"

namespace cem
{
	void PlayerData::Initialize()
	{
		m_Lives = 3;
		m_Score = 0;
	}


	int PlayerData::GetLives()
	{	
		return m_Lives;
	}



	void PlayerData::SetLives(int life)
	{
		m_Lives = life;
	}

	int PlayerData::GetScore()
	{
		return m_Score;
	}

	void PlayerData::SetScore(int score)
	{
		m_Score += score;
	}
}