#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"

class SpriteComponent : public BaseComponent
{
public:
	explicit SpriteComponent(const char* fileName);
	virtual ~SpriteComponent() = default;


	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) noexcept = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

protected:
	void Update(float deltaTime) override;
	void Draw() const override;

private:
	SDL_Texture *m_pTexture;
	SDL_Rect m_SrcRect, m_DestRect;
};

