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
	m_SetBackPos = Vector2f{ 2000.0f,2000.0f };
	m_OriginPos = Vector2f{ 0.0f,0.0f };
	m_ExtraState = ExtraState::Main;

	//background + text
	m_pBgExtraMain = std::make_shared<GameObject>();
	m_pBgExtraMain->AddComponent(std::make_shared<TransformComponent>());
	m_pBgExtraMain->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Extra/bgExtraMain.png"));
	m_ManagerScene.AddChild(m_pBgExtraMain);

	//selector (image of index)
	m_pSelector = std::make_shared<GameObject>();
	m_pSelector->AddComponent(std::make_shared<TransformComponent>());
	m_pSelector->AddComponent(std::make_shared <TextureComponent>("../Resources/Menu/Selector.png"));
	m_ManagerScene.AddChild(m_pSelector);

	//add text (has to be in front of the selector)
	m_pBgExtraMainTxt = std::make_shared<GameObject>();
	m_pBgExtraMainTxt->AddComponent(std::make_shared<TransformComponent>());
	m_pBgExtraMainTxt->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Extra/bgExtraText.png"));
	m_ManagerScene.AddChild(m_pBgExtraMainTxt);

	//background story
	m_pBgStory = std::make_shared<GameObject>();
	m_pBgStory->AddComponent(std::make_shared<TransformComponent>());
	m_pBgStory->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Extra/bgStory.png"));
	m_pBgStory->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
	m_ManagerScene.AddChild(m_pBgStory);


	//background information
	m_pBgInformation = std::make_shared<GameObject>();
	m_pBgInformation->AddComponent(std::make_shared<TransformComponent>());
	m_pBgInformation->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Extra/bgInformation.png"));
	m_pBgInformation->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
	m_ManagerScene.AddChild(m_pBgInformation);


	
	//background credits
	m_pBgCredits = std::make_shared<GameObject>();
	m_pBgCredits->AddComponent(std::make_shared<TransformComponent>());
	m_pBgCredits->AddComponent(std::make_shared<TextureComponent>("../Resources/Menu/Extra/bgCredits.png"));
	m_pBgCredits->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
	m_ManagerScene.AddChild(m_pBgCredits);


	SetImagesBack();


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
	switch (m_ExtraState)
	{
	case MenuExtra::ExtraState::Main:
		m_pBgExtraMain->GetComponent<TransformComponent>()->SetPosition(m_OriginPos);
		m_pBgExtraMainTxt->GetComponent<TransformComponent>()->SetPosition(m_OriginPos);

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
			SetImagesBack();
			m_IsBack = false;
		}
		if (m_IsStory)
		{
			SetImagesBack();
			m_ExtraState = MenuExtra::ExtraState::Story;
			m_IsStory = false;
		}
		if (m_IsInformation)
		{
			SetImagesBack();
			m_ExtraState = MenuExtra::ExtraState::Information;
			m_IsInformation = false;
		}
		if (m_IsCredits)
		{
			SetImagesBack();
			m_ExtraState = MenuExtra::ExtraState::Credits;
			m_IsCredits = false;
		}
		break;
	case MenuExtra::ExtraState::Story:
		m_pBgStory->GetComponent<TransformComponent>()->SetPosition(m_OriginPos);
		SetOriginPos();
		break;
	case MenuExtra::ExtraState::Information:
		m_pBgInformation->GetComponent<TransformComponent>()->SetPosition(m_OriginPos);
		SetOriginPos();
		break;
	case MenuExtra::ExtraState::Credits:
		m_pBgCredits->GetComponent<TransformComponent>()->SetPosition(m_OriginPos);
		SetOriginPos();
		break;
	}

}

void MenuExtra::MoveDown()
{
	if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuExtra
		&& MenuExtra::ExtraState::Main == m_ExtraState)
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
	if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuExtra
		&& MenuExtra::ExtraState::Main == m_ExtraState)
	{
		++m_Index;
		if (m_Index > 3)
		{
			m_Index = 0;
		}

		std::cout << "Index : " << m_Index << std::endl;
	}
}

void MenuExtra::SelectMenu()
{
	if (m_ManagerScene.GetMenuState() == MenuScene::MenuState::menuExtra)
	{
		switch (m_ExtraState)
		{
		case  MenuExtra::ExtraState::Main:
			switch (m_Index)
			{
			case 0:
				m_IsStory = true;
				break;
			case 1:
				m_IsInformation = true;
				break;
			case 2:
				m_IsCredits = true;
				break;
			case 3:
				m_IsBack = true;
				break;
			}
			break;
		case  MenuExtra::ExtraState::Story:
			m_IsMainExtra = true;
			break;
		case  MenuExtra::ExtraState::Information:
			m_IsMainExtra = true;
			break;
		case  MenuExtra::ExtraState::Credits:
			m_IsMainExtra = true;
			break;
		}
	}
}

void MenuExtra::SetImagesBack()
{
	m_pSelector->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
	m_pBgExtraMain->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
	m_pBgExtraMainTxt->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
}

void MenuExtra::SetOriginPos()
{
	if (m_IsMainExtra)
	{
		m_pBgExtraMain->GetComponent<TransformComponent>()->SetPosition(m_OriginPos);
		m_pBgExtraMainTxt->GetComponent<TransformComponent>()->SetPosition(m_OriginPos);
		SetBackEverything();
		m_ExtraState = MenuExtra::ExtraState::Main;
		m_IsMainExtra = false;
	}

}

void MenuExtra::SetBackEverything()
{
	m_pBgStory->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
	m_pBgInformation->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
	m_pBgCredits->GetComponent<TransformComponent>()->SetPosition(m_SetBackPos);
}
