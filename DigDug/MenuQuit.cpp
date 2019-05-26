#include "DigDugPCH.h"
#include "MenuQuit.h"
#include "GameObject.h"
#include "MenuScene.h"
#include "Scene.h"
#include "SoundManager.h"
#include "TransformComponent.h"
#include "CommandManager.h"
#include "TextureComponent.h"
namespace cem
{
	MenuQuit::MenuQuit(MenuScene& managerScene)
		:m_ManagerScene{ managerScene }
	{
		m_Index = 0;
		m_SelectorPos = Vector2f{ 84.0f,457.0f };
		m_ScaleAway = Vector2f{ 0.0f,0.0f };
		m_ScaleNormal = Vector2f{ 1.0f,1.0f };
		//background + text
		m_pBgQuit = std::make_shared<GameObject>();
		m_pBgQuit->AddComponent(std::make_shared<TransformComponent>());
		m_pBgQuit->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Quit/bgQuit.png"));
		m_ManagerScene.AddChild(m_pBgQuit);

		//selector (image of index)
		m_pSelector = std::make_shared<GameObject>();
		m_pSelector->AddComponent(std::make_shared<TransformComponent>());
		m_pSelector->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Selector.png"));
		m_ManagerScene.AddChild(m_pSelector);

		//add text (has to be in front of the selector)
		m_pBqQuitTxt = std::make_shared<GameObject>();
		m_pBqQuitTxt->AddComponent(std::make_shared<TransformComponent>());
		m_pBqQuitTxt->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Quit/bgQuitText.png"));
		m_ManagerScene.AddChild(m_pBqQuitTxt);

#pragma region KeyBindings
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuQuit::MoveDown, this), CommandManager::InputCommands::increment);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuQuit::MoveUp, this), CommandManager::InputCommands::decrement);
		CommandManager::GetInstance().AddCallBack(std::bind(&MenuQuit::SelectMenu, this), CommandManager::InputCommands::select);
#pragma endregion 
		SetImagesBack();
	}

	MenuQuit::~MenuQuit()
	{
	}

	void MenuQuit::Update()
	{
		m_pBqQuitTxt->GetComponent<TransformComponent>()->SetScale(m_ScaleNormal);
		m_pBgQuit->GetComponent<TransformComponent>()->SetScale(m_ScaleNormal);
		m_pSelector->GetComponent<TransformComponent>()->SetScale(m_ScaleNormal);

		switch (m_Index)
		{
		case 0:
			m_SelectorPos = Vector2f{ 84.0f,457.0f };
			break;
		case 1:
			m_SelectorPos = Vector2f{ 84.0f,538.0f };
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



	void MenuQuit::Draw() const
	{
	}

	void MenuQuit::MoveDown()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuQuit)
		{
			--m_Index;
			if (m_Index < 0)
			{
				m_Index = 1;
			}
			SoundManager::GetInstance().PlaySoundEffect("Confirm", false, true);
		}
	}

	void MenuQuit::MoveUp()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuQuit)
		{
			++m_Index;
			if (m_Index > 1)
			{
				m_Index = 0;
			}
			SoundManager::GetInstance().PlaySoundEffect("Confirm", false, true);
		}
	}

	void MenuQuit::SelectMenu()
	{
		if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuQuit)
		{
			switch (m_Index)
			{
			case 0:
				SDL_Event quit;
				quit.type = SDL_QUIT;
				SDL_PushEvent(&quit);
				break;
			case 1:
				m_IsBack = true;
				break;
			}
		}
	}

	void MenuQuit::SetImagesBack()
	{
		m_pSelector->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_pBgQuit->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
		m_pBqQuitTxt->GetComponent<TransformComponent>()->SetScale(m_ScaleAway);
	}
}