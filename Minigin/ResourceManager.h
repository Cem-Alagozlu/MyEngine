#pragma once
#include "Singleton.h"
#include "TextureComponent.h"


class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		ResourceManager() = default;

		void Init();

		std::shared_ptr<TextureComponent> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
	};

