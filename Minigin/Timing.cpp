#include "MiniginPCH.h"
#include "Timing.h"


void Timing::Initialize()
{
	m_PreviousTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = 0;
	m_CurrentTime = m_PreviousTime;
}

void Timing::Update()
{
	m_PreviousTime = m_CurrentTime;
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(m_CurrentTime - m_PreviousTime).count() / 1000.0f;
}

float Timing::GetDeltaTime() const
{
	return m_DeltaTime;
}

int Timing::GetFPS() const
{
	return int(1 / m_DeltaTime);
}
