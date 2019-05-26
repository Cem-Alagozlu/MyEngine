#include "DigDugPCH.h"
#include "MenuMain.h"
#include "GameObject.h"
#include "MenuScene.h"
#include "Scene.h"
#include "SoundManager.h"
#include "CommandManager.h"
#include "TextureComponent.h"
#include "LevelOne.h"

namespace cem
{

	MenuMain::MenuMain(MenuScene & managerScene)
		:m_ManagerScene{ managerScene }
	{
		m_Index = 0;
		m_SelectorPos = Vector2f{ 84.0f,296.0f };
		m_ScaleAway = Vector2f{ 0.0f,0.0f };


	}

	MenuMain::~MenuMain()
	{
	}

	void MenuMain::Initialize()
	{


#pragma region Images
		//background + text
		m_pBgIMG = std::make_shared<GameObject>();
		m_pBgIMG->AddComponent(std::make_shared<TransformComponent>());
		m_pBgIMG->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Main/bgMain.png"));
		m_ManagerScene.AddChild(m_pBgIMG);

		//selector (image of index)
		m_pSelector = std::make_shared<GameObject>();
		m_pSelector->AddComponent(std::make_shared<TransformComponent>());
		m_pSelector->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Selector.png"));
		m_ManagerScene.AddChild(m_pSelector);

		//add text (has to be in front of the selector)
		m_pBgTxt = std::make_shared<GameObject>();
		m_pBgTxt->AddComponent(std::make_shared<TransformComponent>());
		m_pBgTxt->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Main/bgMainText.png"));
		m_ManagerScene.AddChild(m_pBgTxt);

		//GAMEPLAY BUTTONS
		m_PlayButtonPressed = 0;
		m_pGameplay = std::make_shared<GameObject>();
		m_pGameplay->AddComponent(std::make_shared<TransformComponent>());
		m_pGameplay->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Main/bgMainContinue.png"));
		m_pGameplay->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_ManagerScene.AddChild(m_pGameplay);
#pragma endregion 


#pragma region KeyBindings
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuMain::MoveDown, this), CommandManager::InputCommands::increment);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuMain::MoveUp, this), CommandManager::InputCommands::decrement);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuMain::SelectMenu, this), CommandManager::InputCommands::select);
#pragma endregion 

	}

	void MenuMain::Draw() const
	{

	}

	void MenuMain::Update()
	{
		if (m_PlayButtonPressed == 0)
		{
			m_pBgIMG->GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,1.0f });
			m_pBgTxt->GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,1.0f });
			m_pSelector->GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,1.0f });

			switch (m_Index)
			{
			case 0:
				m_SelectorPos = Vector2f{ 84.0f,295.0f };
				break;
			case 1:
				m_SelectorPos = Vector2f{ 84.0f,376.0f };
				break;
			case 2:
				m_SelectorPos = Vector2f{ 84.0f,457.0f };
				break;
			case 3:
				m_SelectorPos = Vector2f{ 84.0f,538.0f };
				break;
			}
			m_pSelector->GetComponent<TransformComponent>()->SetPosition(m_SelectorPos);

		}
		if (m_PlayButtonPressed == 1)
		{
			m_pGameplay->GetComponent<TransformComponent>()->SetScale(Vector2f{ 1.0f,1.0f });
		}

	}

	void MenuMain::MoveDown()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuMain && m_PlayButtonPressed == 0)
		{
			--m_Index;
			if (m_Index < 0)
			{
				m_Index = 3;
			}
			SoundManager::GetInstance().PlaySoundEffect("Confirm", false, true);
		}
	
	}



	void MenuMain::MoveUp()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuMain && m_PlayButtonPressed == 0)
		{
			++m_Index;
			if (m_Index > 3)
			{
				m_Index = 0;
			}
			SoundManager::GetInstance().PlaySoundEffect("Confirm", false, true);
		}

	}

	void MenuMain::SelectMenu()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuMain)
		{
			switch (m_Index)
			{
			case 0:
				++m_PlayButtonPressed;
				if (m_PlayButtonPressed == 2)
				{
					SceneManager::GetInstance().CreateScene(std::make_shared<LevelOne>());
					SceneManager::GetInstance().SetActiveGameScene("LevelOne");
				}
				break;
			case 1:
				SetImagesBack();
				m_ManagerScene.SetMenuState(MenuScene::MenuState::menuExtra);
				break;
			case 2:
				SetImagesBack();
				m_ManagerScene.SetMenuState(MenuScene::MenuState::menuSettings);
				break;
			case 3:
				SetImagesBack();
				m_ManagerScene.SetMenuState(MenuScene::MenuState::menuQuit);
				break;
			}

		}
	
	}

	void MenuMain::SetImagesBack()
	{
		m_pSelector->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_pBgIMG->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_pBgTxt->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
	}
}
