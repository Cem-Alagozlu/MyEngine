#include "MiniginPCH.h"
#include "MenuScene.h"
#include "MenuMain.h"
#include "MenuQuit.h"
#include "MenuExtra.h"
#include "SoundManager.h"
#include "ResourceManager.h"



MenuScene::MenuScene()
	:Scene{"MenuScene"},
	m_pMenuMain{std::make_unique<MenuMain>(*this)},
	m_pMenuQuit{ std::make_unique<MenuQuit>(*this) },
	m_pMenuExtra{ std::make_unique<MenuExtra>(*this) }
{
	SetMenuState(MenuState::menuMain);


	//SoundManager::GetInstance().PlaySoundStream("Menu", true);
}

void MenuScene::SetMenuState(MenuState state)
{
	m_MenuState = state;
	switch (m_MenuState)
	{
	case MenuScene::MenuState::menuMain:
		m_pCurrentMenu = m_pMenuMain.get();
		break;
	case MenuScene::MenuState::menuExtra:
		m_pCurrentMenu = m_pMenuExtra.get();
		break;
	case MenuScene::MenuState::menuQuit:
		m_pCurrentMenu = m_pMenuQuit.get();
		break;
	default:
		m_pCurrentMenu = nullptr;
		break;
	}
}

MenuScene::MenuState MenuScene::GetMenuState()
{
	return m_MenuState;
}

void MenuScene::Initialize()
{
	m_pCurrentMenu->Initialize();
}

void MenuScene::Update()
 {
	m_pCurrentMenu->Update();
}

void MenuScene::Draw()
{
	m_pCurrentMenu->Draw();
}
