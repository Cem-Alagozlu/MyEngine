#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

namespace cem
{
	SpriteComponent::SpriteComponent(const std::string & texture, float sheetLeft, float sheetTop, float sheetWidth, float sheetHeight, int cols, int rows, int framesPerSec)
		: m_SpriteSheetLeft{ sheetLeft }
		, m_SpriteSheetTop{ sheetTop }
		, m_SpriteSheetWidth{ sheetWidth }
		, m_SpriteSheetHeight{ sheetHeight }
		, m_Cols{ cols }
		, m_Rows{ rows }
		, m_FramesPerSec{ framesPerSec }
		, m_Flip{ SDL_FLIP_NONE }
		, m_Angle(0.0)

	{
		m_Offset = Vector2f{ 0.0f,0.0f };
		m_pTexture = ResourceManager::GetInstance().LoadTexture(texture);
		m_SrcRect.width = m_SpriteSheetWidth / m_Cols;
		m_SrcRect.height = m_SpriteSheetHeight / m_Rows;

		UpdateSourceRect();

		m_DestRect.width = m_SpriteSheetWidth / m_Cols;
		m_DestRect.height = m_SpriteSheetHeight / m_Rows;

		m_FrameTime = 1.0f / m_FramesPerSec;
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

	void SpriteComponent::FlipTexture(SDL_RendererFlip flipTexture)
	{
		m_Flip = flipTexture;
	}

	void SpriteComponent::SetAngle(double angle)
	{
		m_Angle = angle;
	}

	void SpriteComponent::SetVisibility(bool isVisible)
	{
		m_IsVisible = isVisible;
	}

	bool SpriteComponent::GetVisibility()
	{
		return m_IsVisible;
	}

	void SpriteComponent::SetOffset(Vector2f offset)
	{
		m_Offset = offset;
	}

	Vector2f SpriteComponent::GetOffset()
	{
		return m_Offset;
	}

	void SpriteComponent::Update(float deltaTime)
	{
		m_AccuSec += deltaTime;
		if (m_AccuSec > m_FrameTime && m_IsLocked == false)
		{
			++m_CurFrame;
			m_CurFrame  %= m_Cols * m_Rows;
			m_AccuSec -= m_FrameTime;
			UpdateSourceRect();
		}
	}

	void SpriteComponent::Draw() const
	{
		if (!m_IsVisible)
		{
			return;
		}

		std::shared_ptr<GameObject> go = m_pGameObject.lock();
		if (go)
		{
			Vector2f pos = go->GetComponent<TransformComponent>()->GetPosition();
			Vector2f scale = go->GetComponent<TransformComponent>()->GetScale();
			Renderer::GetInstance().RenderTexture(m_pTexture, m_SrcRect, pos + m_Offset, scale, m_Angle, m_Flip);
		}
	}

	void SpriteComponent::UpdateSourceRect()
	{
		m_SrcRect.left = m_SpriteSheetLeft + m_CurFrame % m_Cols * m_SrcRect.width;
		m_SrcRect.bottom = m_SpriteSheetTop + (m_CurFrame / m_Cols) * m_SrcRect.height;
	}
}