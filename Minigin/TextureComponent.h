#pragma once
#include "BaseComponent.h"

class TextureComponent : public BaseComponent
{
public:
	SDL_Texture* GetSDLTexture() const;
	explicit TextureComponent(SDL_Texture* texture);

	virtual ~TextureComponent();

	void Update(float deltaTime) override;
	void Draw() const override;

	TextureComponent(const TextureComponent &) = delete;
	TextureComponent(TextureComponent &&) = delete;
	TextureComponent & operator= (const TextureComponent &) = delete;
	TextureComponent & operator= (const TextureComponent &&) = delete;
private:
	SDL_Texture* m_pTexture;
};

