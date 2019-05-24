#pragma once
#include "BaseComponent.h"
#include "TextureComponent.h"
#include "Structs.h"

namespace cem
{
	class Font;

	class TextDrawComponent : public BaseComponent
	{
	public:
		explicit TextDrawComponent(const std::string& text, std::shared_ptr<Font> font, Color3i color = { 255, 255, 255 });

		void Update(float deltaTime) override;
		void Draw() const override;

		void SetText(const std::string& text);


		virtual ~TextDrawComponent() = default;
		TextDrawComponent(const TextDrawComponent& other) = delete;
		TextDrawComponent(TextDrawComponent&& other) = delete;
		TextDrawComponent& operator=(const TextDrawComponent& other) = delete;
		TextDrawComponent& operator=(TextDrawComponent&& other) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<TextureComponent> m_Texture;
		Color3i m_Color;
	};
}