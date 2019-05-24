#include "DigDugPCH.h"
#include "MenuSettings.h"
#include "TextureComponent.h"
#include "MenuScene.h"
#include "CommandManager.h"
#include "Font.h"
#include "TextDrawComponent.h"
#include "ResourceManager.h"

namespace cem
{

	MenuSettings::MenuSettings(MenuScene & managerScene)
		:m_ManagerScene{ managerScene }
	{
		m_Index = 0;
		m_SelectorPos = Vector2f{ 84.0f,330.0f };
		m_ScaleAway = Vector2f{ 0.0f,0.0f };
		m_ScaleNormal = Vector2f{ 1.0f,1.0f };
		auto font = ResourceManager::GetInstance().LoadFont("../Resources/Font/font00.ttf", 10);

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
		m_pMusicText->AddComponent(std::make_shared<TextDrawComponent>("test", font));
		m_ManagerScene.AddChild(m_pMusicText);

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
				std::cout << "VOLUME MUSIC + \n";
				break;
			case 1:
				std::cout << "VOLUME MUSIC - \n";
				break;
			case 2:
				std::cout << "VOLUME SFX + \n";
				break;
			case 3:
				std::cout << "VOLUME SFX - \n";
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
	}
}
