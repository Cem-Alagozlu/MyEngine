#include "DigDugPCH.h"
#include "LevelTwo.h"
#include "SoundManager.h"
#include "Timing.h"
#include "PlayerData.h"

namespace cem
{
	LevelTwo::LevelTwo()
		:Scene{ "LevelTwo" }
	{
	}

	void LevelTwo::Initialize()
	{
		m_Timer = 2.0f;
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

		for (int i = 0; i < 2; i++)
		{
			auto fygar = std::make_shared<Fygar>();
			fygar->Initialize(m_pWorld, m_pPlayer);
			m_pFygars.push_back(fygar);
			AddChild(m_pFygars[i]);
		}
		m_pFygars[0]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 375.0f,225.0f });
		m_pFygars[1]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 75.0f,225.0f });

		m_pRock = std::make_shared<Rock>(m_pWorld);
		m_pRock->Initialize();
		AddChild(m_pRock);

		m_pPlayerHUD = std::make_shared<PlayerHUD>();
		m_pPlayerHUD->Initialize();
		AddChild(m_pPlayerHUD);

		m_pWorld->SetPlayer(m_pPlayer);
		LevelSetup();


		m_pLevelTwoIMG = std::make_shared<GameObject>();
		m_pLevelTwoIMG->AddComponent(std::make_shared<TransformComponent>());
		m_pLevelTwoIMG->AddComponent(std::make_shared<TextureComponent>("../Resources/Level/levelTwo.png"));
		AddChild(m_pLevelTwoIMG);
	}

	void LevelTwo::Update()
	{
		m_Timer -= Timing::GetInstance().GetDeltaTime();

		if (m_Timer <= 0.0f)
		{
			m_pLevelTwoIMG->GetComponent<TextureComponent>()->SetVisibility(false);
		}

		for (auto it = m_pPookas.begin(); it != m_pPookas.end();)
		{
			if ((*it)->IsDead())
			{
				RemoveChild(*it);
				it = m_pPookas.erase(it);
			}
			else
			{
				++it;
			}
		}

		for (auto it = m_pFygars.begin(); it != m_pFygars.end();)
		{
			if ((*it)->IsDead())
			{
				RemoveChild(*it);
				it = m_pFygars.erase(it);
			}
			else
			{
				++it;
			}
		}

		if (m_pFygars.empty()&& m_pPookas.empty())
		{
			PlayerData::GetInstance().SetGameOver(true);
		}

	}

	

	void LevelTwo::Draw()
	{
	}

	void LevelTwo::LevelSetup()
	{
		//MAIN TUNNEL
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
		m_pWorld->GetTunnels()[104]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[105]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[118]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[119]->GetComponent<TextureComponent>()->SetVisibility(true);

		//LEFT FLANK TUNNEL01
		m_pWorld->GetTunnels()[14]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[15]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[16]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[17]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[28]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[29]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[30]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[31]->GetComponent<TextureComponent>()->SetVisibility(true);

		//LEFT FLANK TUNNEL02
		m_pWorld->GetTunnels()[98]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[99]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[100]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[101]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[112]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[113]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[114]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[115]->GetComponent<TextureComponent>()->SetVisibility(true);

		//LEFT FLANK TUNNEL03
		m_pWorld->GetTunnels()[182]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[183]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[184]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[185]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[186]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[196]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[197]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[198]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[199]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[200]->GetComponent<TextureComponent>()->SetVisibility(true);

	
		//RIGHT FLANK TUNNEL01
		m_pWorld->GetTunnels()[24]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[26]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[27]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[28]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[38]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[39]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[40]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[41]->GetComponent<TextureComponent>()->SetVisibility(true);

		//RIGHT FLANK TUNNEL02
		m_pWorld->GetTunnels()[108]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[109]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[110]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[111]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[122]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[123]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[124]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[125]->GetComponent<TextureComponent>()->SetVisibility(true);

		//RIGHT FLANK TUNNEL03
		m_pWorld->GetTunnels()[191]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[192]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[193]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[194]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[195]->GetComponent<TextureComponent>()->SetVisibility(true);

		m_pWorld->GetTunnels()[205]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[206]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[207]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[208]->GetComponent<TextureComponent>()->SetVisibility(true);
		m_pWorld->GetTunnels()[209]->GetComponent<TextureComponent>()->SetVisibility(true);
	}
}
