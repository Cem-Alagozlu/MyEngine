#include "DigDugPCH.h"
#include "LevelOne.h"
#include "TextureComponent.h"
#include "SoundManager.h"

namespace cem
{
	LevelOne::LevelOne()
		:Scene{ "LevelOne" }
	{
	}



	void LevelOne::Initialize()
	{
		SoundManager::GetInstance().StopAll();
		m_pWorld = std::make_shared<World>();
		AddChild(m_pWorld);
		m_pWorld->Initialize(*this);

		m_pPlayer = std::make_shared<Player>();
		m_pPlayer->Initialize();
		m_pPlayer->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 210.0f,285.0f });
		AddChild(m_pPlayer);

		
		for (int i = 0; i < 2; i++)
		{
			auto pooka = std::make_shared<Pooka>();
			pooka->Initialize(m_pWorld, m_pPlayer);
			m_pPookas.push_back(pooka);
			AddChild(m_pPookas[i]);
		}
		
		m_pPookas[0]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 375.0f,525.0f });
		m_pPookas[1]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 75.0f,525.0f });
	

		m_pFygar = std::make_shared<Fygar>();
		m_pFygar->Initialize(m_pWorld, m_pPlayer);
		m_pFygar->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 250.0f,600.0f });
		AddChild(m_pFygar);

		m_pFruits = std::make_shared<PickUpFruit>();
		m_pFruits->Initialize();
		AddChild(m_pFruits);


		m_pPlayerHUD = std::make_shared<PlayerHUD>();
		m_pPlayerHUD->Initialize();
		AddChild(m_pPlayerHUD);

		m_pWorld->SetPlayer(m_pPlayer);
		LevelSetup();


	}

	void LevelOne::Update()
	{
		std::cout << "Level Scene\n";
	}

	void LevelOne::Draw()
	{
	}

	void LevelOne::LevelSetup()
	{
#pragma region levelSetup
		//FIRST TUNNEL
		m_pWorld->GetTunnels()[6]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[7]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[20]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[21]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[34]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[35]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[48]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[49]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[62]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[63]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[76]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[77]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[90]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[91]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[102]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[103]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[104]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[105]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[106]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[107]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[116]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[117]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[118]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[119]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[120]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[121]->GetComponent<TextureComponent>()->SetVisibility(true);

		//SECOND TUNNEL
		m_pWorld->GetTunnels()[183]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[184]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[185]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[197]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[198]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[199]->GetComponent<TextureComponent>()->SetVisibility(true);

		//THIRD TUNNEL
		m_pWorld->GetTunnels()[192]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[193]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[194]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[206]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[207]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[208]->GetComponent<TextureComponent>()->SetVisibility(true);

		//FOURTH TUNNEL 
		m_pWorld->GetTunnels()[243]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[244]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[245]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[246]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[257]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[258]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[259]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[260]->GetComponent<TextureComponent>()->SetVisibility(true);
#pragma endregion
	}

}
