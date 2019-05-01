#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"

SDL_Texture * TextureComponent::GetSDLTexture() const
{
	return m_pTexture;
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
	std::shared_ptr<GameObject> go = m_pGameObject.lock();
	if (go)
	{
		Vector2f pos = go->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*this, pos);
	}
}

