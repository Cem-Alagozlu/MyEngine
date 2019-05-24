#include "DigDugPCH.h"
#include "MenuSettings.h"
#include "TextureComponent.h"
#include "MenuScene.h"
#include "CommandManager.h"
#include "Font.h"
#include "TextDrawComponent.h"
#include "ResourceManager.h"
#include "SoundManager.h"

namespace cem
{

	MenuSettings::MenuSettings(MenuScene & managerScene)
		:m_ManagerScene{ managerScene }
	{
		m_Index = 0;
		m_SelectorPos = Vector2f{ 84.0f,330.0f };
		m_ScaleAway = Vector2f{ 0.0f,0.0f };
		m_ScaleNormal = Vector2f{ 1.0f,1.0f };
		auto font = ResourceManager::GetInstance().LoadFont("../Resources/Font/font00.ttf", 25);

		//background settings
		m_pBgSettings = std::make_shared<GameObject>();
		m_pBgSettings->AddComponent(std::make_shared<TransformComponent>());
		m_pBgSettings->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Settings/bgSettings.png"));
		m_pBgSettings->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_ManagerScene.AddChild(m_pBgSettings);

		//SelectorSmall
		m_pSelector = std::make_shared<GameObject>();
		m_pSelector->AddComponent(std::make_shared<TransformComponent>());
		m_pSelector->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/SelectorSmall.png"));
		m_pSelector->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_ManagerScene.AddChild(m_pSelector);

		//Music Text
		m_pMusicText = std::make_shared<GameObject>();
		m_pMusicText->AddComponent(std::make_shared<TransformComponent>());
		m_pMusicText->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 160.0f,330.0f });
		m_pMusicText->AddComponent(std::make_shared<TextDrawComponent>("0", font));
		m_pMusicText->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_ManagerScene.AddChild(m_pMusicText);

		//SFX Text
		m_pSoundEffectText = std::make_shared<GameObject>();
		m_pSoundEffectText->AddComponent(std::make_shared<TransformComponent>());
		m_pSoundEffectText->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 160.0f,520.0f });
		m_pSoundEffectText->AddComponent(std::make_shared<TextDrawComponent>("0", font));
		m_pSoundEffectText->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_ManagerScene.AddChild(m_pSoundEffectText);

		CommandManager::GetInstance().AddCallBack(std::bind(&MenuSettings::MoveDown, this), CommandManager::InputCommands::increment);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuSettings::MoveUp, this), CommandManager::InputCommands::decrement);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuSettings::Select, this), CommandManager::InputCommands::select);
	}

	MenuSettings::~MenuSettings()
	{
	}

	void MenuSettings::Draw() const
	{
	}

	void MenuSettings::Update()
	{
		m_pBgSettings->GetComponent<TransformComponent>()->SetScale(m_ScaleNormal);
		m_pSelector->GetComponent<TransformComponent>()->SetScale(m_ScaleNormal);
		m_pMusicText->GetComponent<TransformComponent>()->SetScale(m_ScaleNormal);
		m_pSoundEffectText->GetComponent<TransformComponent>()->SetScale(m_ScaleNormal);

		switch (m_Index)
		{
		case 0:
			m_SelectorPos = Vector2f{ 84.0f,330.0f };
			break;
		case 1:
			m_SelectorPos = Vector2f{ 84.0f,378.0f };
			break;
		case 2:
			m_SelectorPos = Vector2f{ 84.0f,513.0f };
			break;
		case 3:
			m_SelectorPos = Vector2f{ 84.0f,561.0f };
			break;
		case 4:
			m_SelectorPos = Vector2f{ 84.0f,626.0f };
			break;
		}
		m_pSelector->GetComponent<TransformComponent>()->SetPosition(m_SelectorPos);

		if (m_IsBack)
		{

			m_ManagerScene.SetMenuState(MenuScene::MenuState::menuMain);
			SetImagesBack();
			m_IsBack = false;
		}

		m_pMusicText->GetComponent<TextDrawComponent>()->SetText(std::to_string(SoundManager::GetInstance().GetVolumeSoundStream()));
		m_pSoundEffectText->GetComponent<TextDrawComponent>()->SetText(std::to_string(SoundManager::GetInstance().GetVolumeSoundEffect()));
	}

	void MenuSettings::MoveUp()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuSettings)
		{
			++m_Index;
			if (m_Index > 4)
			{
				m_Index = 0;
			}
			std::cout << "Index : " << m_Index << std::endl;
		}
	}

	void MenuSettings::MoveDown()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuSettings)
		{
			--m_Index;
			if (m_Index < 0)
			{
				m_Index = 4;
			}
			std::cout << "Index : " << m_Index << std::endl;
		}
	}

	void MenuSettings::Select()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuSettings)
		{
			switch (m_Index)
			{
			case 0:
				SoundManager::GetInstance().VolumeUpSoundStream();
				break;
			case 1:
				SoundManager::GetInstance().VolumeDownSoundStream();
				break;
			case 2:
				SoundManager::GetInstance().VolumeUpSoundEffect();
				break;
			case 3:
				SoundManager::GetInstance().VolumeDownSoundEffect();
				break;
			case 4:
				m_IsBack = true;
				break;
			}
		}
	}

	void MenuSettings::SetImagesBack()
	{
		m_pSelector->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_pBgSettings->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_pMusicText->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_pSoundEffectText->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
	}
}
