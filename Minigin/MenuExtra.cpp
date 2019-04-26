#include "MiniginPCH.h"
#include "MenuExtra.h"
#include "ResourceManager.h"
#include "CommandManager.h"
#include "MenuScene.h"

MenuExtra::MenuExtra(MenuScene& managerScene)
	:m_ManagerScene{ managerScene }
{
	m_Index = 0;
	m_SelectorPos = Vector2f{ 84.0f,296.0f };
	//background + text
	m_pBgExtraMain = std::make_shared<GameObject>();
	m_pBgExtraMain->AddComponent(std::make_shared<TransformComponent>());
	auto bgMainExtraIMG01 = ResourceManager::GetInstance().LoadTexture("../Resources/Menu/Extra/bgExtraMain.png");
	m_pBgExtraMain->AddComponent(bgMainExtraIMG01);
	m_ManagerScene.AddChild(m_pBgExtraMain);

	//selector (image of index)
	m_pSelector = std::make_shared<GameObject>();
	m_pSelector->AddComponent(std::make_shared<TransformComponent>());
	auto selectorImage = ResourceManager::GetInstance().LoadTexture("../Resources/Menu/Selector.png");
	m_pSelector->AddComponent(selectorImage);
	m_ManagerScene.AddChild(m_pSelector);

	//add text (has to be in front of the selector)
	m_pBqExtraMainTxt = std::make_shared<GameObject>();
	m_pBqExtraMainTxt->AddComponent(std::make_shared<TransformComponent>());
	auto bgExtraMainTxt = ResourceManager::GetInstance().LoadTexture("../Resources/Menu/Extra/bgExtraText.png");
	m_pBqExtraMainTxt->AddComponent(bgExtraMainTxt);
	m_ManagerScene.AddChild(m_pBqExtraMainTxt);

	m_Index = 0;


#pragma region KeyBindings
	CommandManager::GetInstance().AddCallBack(std::bind(&MenuExtra::MoveDown, this), CommandManager::InputCommands::increment);
	CommandManager::GetInstance().AddCallBack(std::bind(&MenuExtra::MoveUp, this), CommandManager::InputCommands::decrement);
	CommandManager::GetInstance().AddCallBack(std::bind(&MenuExtra::SelectMenu, this), CommandManager::InputCommands::select);
#pragma endregion 
}

MenuExtra::~MenuExtra()
{
}

void MenuExtra::Draw() const
{
}

void MenuExtra::Update()
{
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


	if (m_IsBack)
	{
		m_ManagerScene.SetMenuState(MenuScene::MenuState::menuMain);
		m_IsBack = false;
	}
}

void MenuExtra::MoveDown()
{
	if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuExtra)
	{
		--m_Index;
		if (m_Index < 0)
		{
			m_Index = 3;
		}
		std::cout << "Index : " << m_Index << std::endl;
	}
}

void MenuExtra::MoveUp()
{
	if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuExtra)
	{
		++m_Index;
		if (m_Index > 3)
		{
			m_Index = 0;
		}

		std::cout << "Index : " << m_Index << std::endl;
	}
}
//testing
void MenuExtra::SelectMenu()
{
	if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuExtra)
	{
		switch (m_Index)
		{
		case 0:
			std::cout << "Play Game!\n";
			break;
		case 1:
			//m_ManagerScene.SetMenuState()
			std::cout << "Extra!\n";
			break;
		case 2:
			//m_ManagerScene.SetMenuState()
			std::cout << "Settings!\n";
			break;
		case 3:
			m_IsBack = true;
			break;
		}
	}
}
