#pragma once
#include "Singleton.h"

class Time final : public Singleton<Time>
{
public:
	void Initialize();
	void Update();

	float GetDeltaTime() const;
	int GetFPS() const;

private:
	std::chrono::high_resolution_clock::time_point m_CurrentTime, m_PreviousTime;
	float m_DeltaTime;
};

