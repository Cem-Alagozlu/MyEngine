#pragma once
#include "Scene.h"
#include "IMenu.h"

//const & -> no copy of large data

class MenuManager;
class MenuMain;
class MenuQuit;
class MenuExtra;

class MenuScene  : public Scene
{
public:
	enum class MenuState
	{
		menuMain,
		menuQuit,
		menuOption,
		menuExtra,
		menuIntro
	};

	MenuScene();
	virtual ~MenuScene() = default;

	void SetMenuState(MenuState state);
	MenuState GetMenuState();

	MenuScene(const MenuScene& other) = delete;
	MenuScene(MenuScene&& other) noexcept = delete;
	MenuScene& operator=(const MenuScene& other) = delete;
	MenuScene& operator=(MenuScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	MenuState m_MenuState;
	std::unique_ptr<MenuMain> m_pMenuMain;
	std::unique_ptr<MenuQuit> m_pMenuQuit;
	std::unique_ptr<MenuExtra> m_pMenuExtra;
	IMenu* m_pCurrentMenu;

};

