#include "DigDugPCH.h"
#include "PlayerHUD.h"
#include "TextureComponent.h"
#include "PlayerData.h"
#include "ResourceManager.h"
#include "TextDrawComponent.h"


namespace cem
{
	PlayerHUD::PlayerHUD()
	{
		
	}


	PlayerHUD::~PlayerHUD()
	{
	}

	void PlayerHUD::Initialize()
	{
		auto font = ResourceManager::GetInstance().LoadFont("../Resources/Font/font00.ttf", 20);

		m_TotalLives = PlayerData::GetInstance().GetLives();

		//SCORE TEXT
		m_pScoreTXT = std::make_shared<GameObject>();
		m_pScoreTXT->AddComponent(std::make_shared<TransformComponent>());
		m_pScoreTXT->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 450.0f,55.0f });
		m_pScoreTXT->AddComponent(std::make_shared<TextDrawComponent>("TESTING BOIIIIII", font));

		//LIVES
		for (int i = 0; i < m_TotalLives; i++)
		{		
			auto lifeIMG = std::make_shared<GameObject>();
			lifeIMG->AddComponent(std::make_shared<TransformComponent>());
			lifeIMG->AddComponent(std::make_shared<TextureComponent>("../Resources/Character/DigDug/Life.png"));
			lifeIMG->GetComponent<TransformComponent>()->SetScale(Vector2f{ 0.25f,0.25f });
			m_pLivesIMG.push_back(lifeIMG);
		}

		m_pGameOverIMG = std::make_shared<GameObject>();
		m_pGameOverIMG->AddComponent(std::make_shared<TransformComponent>());
		m_pGameOverIMG->AddComponent(std::make_shared<TextureComponent>("../Resources/Environment/gameOver.png"));
	}

	void PlayerHUD::Update(float deltaTime)
	{
		m_TotalLives = PlayerData::GetInstance().GetLives();
		for (int i = 0; i < m_TotalLives; i++)
		{
			m_pLivesIMG[i]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 453.0f + (i * 30.0f),655.0f });
		}

		m_pScoreTXT->Update(deltaTime);
		m_pScoreTXT->GetComponent<TextDrawComponent>()->SetText(std::to_string(PlayerData::GetInstance().GetScore()));
	}

	void PlayerHUD::Draw() const
	{
		for (int i = 0; i < m_TotalLives; i++)
		{
			m_pLivesIMG[i]->Draw();
		}
	
		m_pScoreTXT->Draw();

		if (PlayerData::GetInstance().GetGameOver())
		{
			m_pGameOverIMG->Draw();
		}
	}
}
