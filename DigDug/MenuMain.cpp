#include "DigDugPCH.h"
#include "MenuMain.h"
#include "GameObject.h"
#include "MenuScene.h"
#include "Scene.h"
#include "SoundManager.h"
#include "CommandManager.h"
#include "TextureComponent.h"
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
#pragma endregion 


#pragma region KeyBindings
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuMain::MoveDown, this), CommandManager::InputCommands::increment);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuMain::MoveUp, this), CommandManager::InputCommands::decrement);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuMain::SelectMenu, this), CommandManager::InputCommands::select);
#pragma endregion 


		//m_pSprite = std::make_shared<GameObject>();
		//m_pSprite->AddComponent(std::make_shared<SpriteComponent>("../Resources/walk.png", 0.0f, 0.0f, 5882.0f, 1794.0f, 4, 1, 6));
		//m_pSprite->AddComponent(std::make_shared<TransformComponent>());
		//m_pSprite->GetComponent<TransformComponent>()->SetScale(Vector2f{ 0.1f, 0.1f });
		//m_ManagerScene.AddChild(m_pSprite);
	}

	void MenuMain::Draw() const
	{

	}

	void MenuMain::Update()
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

	void MenuMain::MoveDown()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuMain)
		{
			--m_Index;
			if (m_Index < 0)
			{
				m_Index = 3;
			}
			std::cout << "Index : " << m_Index << std::endl;
		}
	}



	void MenuMain::MoveUp()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuMain)
		{
			++m_Index;
			if (m_Index > 3)
			{
				m_Index = 0;
			}

			std::cout << "Index : " << m_Index << std::endl;
		}
	}

	void MenuMain::SelectMenu()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuMain)
		{
			switch (m_Index)
			{
			case 0:
				std::cout << "Play Game!\n";
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