#include "MiniginPCH.h"
#include "Time.h"


void Time::Initialize()
{
	m_PreviousTime = std::chrono::high_resolution_clock::now();
}

void Time::Update()
{
	m_PreviousTime = m_CurrentTime;
	m_CurrentTime = std::chrono::high_resolution_clock::now();
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

int Time::GetFPS() const
{
	return int(1 / m_DeltaTime);
}
