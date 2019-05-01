#include "MiniginPCH.h"
#include "Time.h"


void Time::Initialize()
{
	m_PreviousTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = 0;
	m_CurrentTime = m_PreviousTime;
}

void Time::Update()
{
	m_PreviousTime = m_CurrentTime;
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_CurrentTime - m_PreviousTime).count() / 1000.0f;
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

int Time::GetFPS() const
{
	return int(1 / m_DeltaTime);
}
