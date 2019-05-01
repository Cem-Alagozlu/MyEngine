#include "MiniginPCH.h"
#include "TextDrawComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include "Font.h"
#include "TransformComponent.h"
#include "GameObject.h"

TextDrawComponent::TextDrawComponent(const std::string & text, std::shared_ptr<Font> font, Color3i color)
	:m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
	, m_Texture(nullptr)
	, m_Color(color)
{
}

void TextDrawComponent::Update(float /*deltaTime*/)
{
	if (m_NeedsUpdate)
	{
		SDL_Color color;
		color.r = static_cast<Uint8>(m_Color.r);
		color.g = static_cast<Uint8>(m_Color.g);
		color.b = static_cast<Uint8>(m_Color.b);
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<TextureComponent>(texture);
	}
}

void TextDrawComponent::Draw() const
{
	std::shared_ptr<GameObject> go = m_pGameObject.lock();
	if (go)
	{
		Vector2f pos = go->GetComponent<TransformComponent>()->GetPosition();
		if (m_Texture != nullptr)
		{
			Vector2f scale = go->GetComponent<TransformComponent>()->GetScale();
			Renderer::GetInstance().GetInstance().RenderTexture(m_Texture->GetSDLTexture(), pos,scale);
		}
	}

}

void TextDrawComponent::SetText(const std::string & text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
