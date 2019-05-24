#pragma once
#include "Singleton.h"
#include "Structs.h"

struct SDL_Window;
struct SDL_Renderer;

namespace cem
{
	class TextureComponent;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;
	public:
		void Init(SDL_Window* window);
		void Draw();
		void Destroy();

		void RenderTexture(SDL_Texture* texture, Vector2f pos, Vector2f scale) const;
		void RenderTexture(SDL_Texture* texture, Rectf srcRect, Vector2f pos, Vector2f scale, double angle = 0.0, SDL_RendererFlip flipTexture = SDL_FLIP_NONE) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}