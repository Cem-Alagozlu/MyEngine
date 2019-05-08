#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"

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

void Renderer::RenderTexture(SDL_Texture* texture,Vector2f pos,Vector2f scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	dst.w = int(dst.w * scale.x);
	dst.h = int(dst.h * scale.y);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void Renderer::RenderTexture(SDL_Texture* texture, Rectf srcRect, Vector2f pos, Vector2f scale) const
{
	SDL_Rect dst;
	SDL_Rect sdlSrcRect{0,0,5000,2000};
	UNREFERENCED_PARAMETER(scale);
	UNREFERENCED_PARAMETER(srcRect);
	sdlSrcRect.x = int(srcRect.left);
	sdlSrcRect.y = int(srcRect.bottom);
	sdlSrcRect.w = int(srcRect.width);
	sdlSrcRect.h = int(srcRect.height );

	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	dst.w = int(dst.w * scale.x);
	dst.h = int(dst.h * scale.y);
	SDL_RenderCopy(GetSDLRenderer(), texture, &sdlSrcRect, &dst);
}

//
//void Renderer::RenderTexture(SDL_Texture* texture, Vector2f pos, const float width, const float height) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(pos.x);
//	dst.y = static_cast<int>(pos.y);
//	dst.w = static_cast<int>(width);
//	dst.h = static_cast<int>(height);
//	SDL_RenderCopy(GetSDLRenderer(),texture, nullptr, &dst);
//}
