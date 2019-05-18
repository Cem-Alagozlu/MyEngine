#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

SDL_Texture * TextureComponent::GetSDLTexture() const
{
	return m_pTexture;
}

TextureComponent::TextureComponent(const std::string& texture )
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texture);
}

TextureComponent::TextureComponent(SDL_Texture * texture)
{
	m_pTexture = texture;
}

TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_pTexture);
}

void TextureComponent::Update(float /*deltaTime*/)
{
}

void TextureComponent::Draw() const
{
	if (!m_IsVisible)
	{
		return;
	}
	std::shared_ptr<GameObject> go = m_pGameObject.lock();
	if (go)
	{
		Vector2f pos = go->GetComponent<TransformComponent>()->GetPosition();
		Vector2f scale = go->GetComponent<TransformComponent>()->GetScale();
		Renderer::GetInstance().RenderTexture(this->GetSDLTexture(),pos,scale);
	}
}

void TextureComponent::SetVisibility(bool isVisible)
{
	m_IsVisible = isVisible;
}

bool TextureComponent::GetVisibility()
{
	return m_IsVisible;
}

