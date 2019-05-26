#include "DigDugPCH.h"
#include "PlayerHUD.h"
#include "TextureComponent.h"
#include "PlayerData.h"
#include "ResourceManager.h"
#include "TextDrawComponent.h"
#include "Timing.h"


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

		//SCORE TEXT
		m_pScoreTXT = std::make_shared<GameObject>();
		m_pScoreTXT->AddComponent(std::make_shared<TransformComponent>());
		m_pScoreTXT->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 450.0f,55.0f });
		m_pScoreTXT->AddComponent(std::make_shared<TextDrawComponent>("test", font));

		//LIVES
		for (int i = 0; i < PlayerData::GetInstance().GetLives(); i++)
		{		
			auto lifeIMG = std::make_shared<GameObject>();
			lifeIMG->AddComponent(std::make_shared<TransformComponent>());
			lifeIMG->AddComponent(std::make_shared<TextureComponent>("../Resources/Character/DigDug/Life.png"));
			lifeIMG->GetComponent<TransformComponent>()->SetScale(Vector2f{ 0.25f,0.25f });
			m_pLivesIMG.push_back(lifeIMG);
		}

		//ACHIEVEMENTS
		for (int i = 0; i < m_TotalAchievements; i++)
		{
			auto achievements = std::make_shared<GameObject>();
			achievements->AddComponent(std::make_shared<TransformComponent>());
			std::stringstream str;
			str << "../Resources/Environment/Achievements/img (" << i + 1 << ")" << ".png";
			achievements->AddComponent(std::make_shared<TextureComponent>(str.str()));
			achievements->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 448.0f,200.0f });
			m_pAchievments.push_back(achievements);
		}

		for (int i = 0; i < m_TotalAchievements; i++)
		{
			auto overlay = std::make_shared<GameObject>();
			overlay->AddComponent(std::make_shared<TransformComponent>());
			overlay->AddComponent(std::make_shared<TextureComponent>("../Resources/Environment/Achievements/empty.png"));
			overlay->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 448.0f,200.0f });
			m_pAchievemntsOverlay.push_back(overlay);
		}

		m_HasAchievement = false;
		m_AchievementTimer = 2.0f;
		m_pAchievementUnlockedIMG = std::make_shared<GameObject>();
		m_pAchievementUnlockedIMG->AddComponent(std::make_shared<TransformComponent>());
		m_pAchievementUnlockedIMG->AddComponent(std::make_shared<TextureComponent>("../Resources/Environment/Achievements/Unlocked.png"));

		m_pGameOverIMG = std::make_shared<GameObject>();
		m_pGameOverIMG->AddComponent(std::make_shared<TransformComponent>());
		m_pGameOverIMG->AddComponent(std::make_shared<TextureComponent>("../Resources/Environment/gameOver.png"));
	}

	void PlayerHUD::Update(float deltaTime)
	{
	
		for (int i = 0; i < PlayerData::GetInstance().GetLives(); i++)
		{
			m_pLivesIMG[i]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 453.0f + (i * 30.0f),655.0f });
		}

		m_pScoreTXT->Update(deltaTime);
		m_pScoreTXT->GetComponent<TextDrawComponent>()->SetText(std::to_string(PlayerData::GetInstance().GetScore()));


		for (int i = 0; i < m_pAchievments.size(); i++)
		{
			m_pAchievments[i]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 448.0f,200.0f + (i*40) });
		}
		for (int i = 0; i < m_pAchievments.size(); i++)
		{
			m_pAchievemntsOverlay[i]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 448.0f,200.0f + (i * 40) });
		}

		//ACHIEVEMENTS
		for (int i = 0; i < m_pAchievemntsOverlay.size(); i++)
		{
				if (PlayerData::GetInstance().GetAchievements(static_cast<PlayerData::PlayerAchievements>(i))
					&& m_pAchievemntsOverlay[i]->GetComponent<TextureComponent>()->GetVisibility())
				{
					m_HasAchievement = true;
					m_pAchievemntsOverlay[i]->GetComponent<TextureComponent>()->SetVisibility(false);
				}
		}


		
		if (m_HasAchievement)
		{
			m_AchievementTimer -= Timing::GetInstance().GetDeltaTime();
			if (m_AchievementTimer <= 0.0f)
			{
				m_HasAchievement = false;
			}
		}


		if (!m_HasAchievement)
		{
			m_AchievementTimer = 2.0f;

		}
		
	}

	void PlayerHUD::Draw() const
	{
		for (int i = 0; i < PlayerData::GetInstance().GetLives(); i++)
		{
			m_pLivesIMG[i]->Draw();
		}
	
		m_pScoreTXT->Draw();



		for (size_t i = 0; i < m_pAchievments.size(); i++)
		{
			m_pAchievments[i]->Draw();
		}

		for (size_t i = 0; i < m_pAchievments.size(); i++)
		{
			m_pAchievemntsOverlay[i]->Draw();
		}

		if (m_HasAchievement)
		{
			m_pAchievementUnlockedIMG->Draw();
		}

		if (PlayerData::GetInstance().GetGameOver())
		{
			m_pGameOverIMG->Draw();
		}
	}
}
