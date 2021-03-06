#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace cem
{
	class SpriteComponent final : public BaseComponent
	{
	public:
		explicit SpriteComponent(const std::string& texture, float sheetLeft, float sheetTop, float sheetWidth, float sheetHeight, int cols, int rows, int framesPerSec);
		virtual ~SpriteComponent() = default;

		float GetWidth() const;
		float GetHeight() const;
		bool HasEnded() const;
		void Lock();
		void Unlock();

		void FlipTexture(SDL_RendererFlip flipTexture);
		void SetAngle(double angle);
		void SetVisibility(bool isVisible);
		bool GetVisibility();
		void SetOffset(Vector2f offset);
		Vector2f GetOffset();


		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

	protected:
		void Update(float deltaTime) override;
		void Draw() const override;


	private:
		SDL_Texture *m_pTexture;
		Rectf m_SrcRect, m_DestRect;
		float m_AccuSec{};
		int m_CurFrame{};
		bool m_IsLocked{ false };
		bool m_IsVisible{ true };
		Vector2f m_Offset;
		const float m_SpriteSheetLeft;
		const float m_SpriteSheetTop;
		const float m_SpriteSheetWidth;
		const float m_SpriteSheetHeight;
		const int m_Cols;
		const int m_Rows;
		int m_FramesPerSec;
		float m_FrameTime;
		float m_Scale;
		SDL_RendererFlip m_Flip;
		double m_Angle;
		void UpdateSourceRect();
	};
}