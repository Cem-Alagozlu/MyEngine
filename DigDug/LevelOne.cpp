#include "DigDugPCH.h"
#include "LevelOne.h"
#include "TextureComponent.h"

namespace cem
{
	LevelOne::LevelOne()
		:Scene{ "LevelOne" }
	{
	}



	void LevelOne::Initialize()
	{
		m_pWorld = std::make_shared<World>();
		AddChild(m_pWorld);
		m_pWorld->Initialize(*this);

		m_pPlayer = std::make_shared<Player>();
		m_pPlayer->Initialize();
		AddChild(m_pPlayer);

		m_pPooka = std::make_shared<Pooka>();
		m_pPooka->Initialize(m_pWorld, m_pPlayer);
		m_pPooka->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 250.0f, 250.0f });
		AddChild(m_pPooka);

		m_pWorld->SetPlayer(m_pPlayer);
	}

	void LevelOne::Update()
	{
	}

	void LevelOne::Draw()
	{
	}
}
