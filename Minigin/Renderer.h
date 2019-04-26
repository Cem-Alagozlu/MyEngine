#pragma once
#include "Singleton.h"
#include "Structs.h"
#include "TextureComponent.h"

struct SDL_Window;
struct SDL_Renderer;


class TextureComponent;
class Renderer final : public Singleton<Renderer>
{
	SDL_Renderer* mRenderer = nullptr;
	public:
	void Init(SDL_Window* window);
	void Draw();
	void Destroy();

	void RenderTexture(const TextureComponent& texture, Vector2f pos) const;
	void RenderTexture(const TextureComponent& texture, Vector2f pos, float width, float height) const;

	SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
};

