#pragma once
#include "Singleton.h"
#include "Structs.h"

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

	void RenderTexture( SDL_Texture* texture, Vector2f pos,Vector2f scale) const;
	void RenderTexture(SDL_Texture* texture,Rectf srcRect ,Vector2f pos, Vector2f scale) const;
	//void RenderTexture( SDL_Texture* texture, Vector2f pos, float width, float height) const;

	SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
};

