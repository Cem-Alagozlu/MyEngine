#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "TextureComponent.h"

void Renderer::Init(SDL_Window * window)
{
	//SDL_RENDERER_PRESENTVSYNC
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Draw()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Draw();
	
	SDL_RenderPresent(mRenderer);
}

void Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void Renderer::RenderTexture(const TextureComponent& texture,Vector2f pos) const
{

	SDL_Rect dst;
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const TextureComponent& texture, Vector2f pos, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
