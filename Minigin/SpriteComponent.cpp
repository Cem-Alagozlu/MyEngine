#include "MiniginPCH.h"
#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(const std::string & texture, float sheetLeft, float sheetTop, float sheetWidth, float sheetHeight, int cols, int rows, int framesPerSec)
	: m_SpriteSheetLeft{ sheetLeft }
	, m_SpriteSheetTop{ sheetTop }
	, m_SpriteSheetWidth{ sheetWidth }
	, m_SpriteSheetHeight{ sheetHeight }
	, m_Cols{ cols }
	, m_Rows{ rows }
	, m_FramesPerSec{ framesPerSec }
	
{
	m_SrcRect.width = m_SpriteSheetWidth / m_Cols;
	m_SrcRect.height = m_SpriteSheetHeight / m_Rows;

	UpdateSourceRect();

	m_DestRect.width = m_SpriteSheetWidth / m_Cols;
	m_DestRect.height = m_SpriteSheetHeight / m_Rows;

	m_FrameTime = 1.0f / m_FramesPerSec;
}

void SpriteComponent::Draw(bool flipped) const
{
}

bool SpriteComponent::HasEnded() const
{
	if ((m_CurFrame + 1) / m_Cols == 1)
	{
		return true;
	}
	return false;
}

void SpriteComponent::Lock()
{
	m_IsLocked = true;
}

void SpriteComponent::Unlock()
{
	m_IsLocked = false;
	m_CurFrame = 0;
	m_AccuSec = 0.0f;
}

void SpriteComponent::Update(float deltaTime)
{
	m_AccuSec += deltaTime;
	if (m_AccuSec > m_FrameTime && m_IsLocked == false)
	{
		++m_CurFrame %= m_Cols * m_Rows;
		m_AccuSec -= m_FrameTime;
		UpdateSourceRect();
	}
}

void SpriteComponent::Draw() const
{

}

void SpriteComponent::UpdateSourceRect()
{
	m_SrcRect.left = m_SpriteSheetLeft + m_CurFrame % m_Cols * m_SrcRect.width;
	m_SrcRect.bottom = m_SpriteSheetTop + (m_CurFrame / m_Cols + 1) * m_SrcRect.height;
}
