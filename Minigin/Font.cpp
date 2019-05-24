#include "MiniginPCH.h"
#include "Font.h"

namespace cem
{
	TTF_Font* Font::GetFont() const {
		return mFont;
	}

	Font::Font(const std::string& fullPath, unsigned size) : mFont(nullptr), mSize(size)
	{
		mFont = TTF_OpenFont(fullPath.c_str(), size);
		if (mFont == nullptr)
		{
			std::cout << SDL_GetError() << std::endl;
			throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
		}
	}

	Font::~Font()
	{
		TTF_CloseFont(mFont);
	}
}