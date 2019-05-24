#pragma once
#include "BaseComponent.h"

namespace cem
{
	class TextureComponent : public BaseComponent
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit TextureComponent(const std::string& texture);
		explicit TextureComponent(SDL_Texture* texture);

		virtual ~TextureComponent();

		void Update(float deltaTime) override;
		void Draw() const override;

		void SetVisibility(bool isVisible);
		bool GetVisibility();

		TextureComponent(const TextureComponent &) = delete;
		TextureComponent(TextureComponent &&) = delete;
		TextureComponent & operator= (const TextureComponent &) = delete;
		TextureComponent & operator= (const TextureComponent &&) = delete;
	private:
		SDL_Texture* m_pTexture;
		bool m_IsVisible = true;
	};
}

