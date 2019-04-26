#pragma once
#include "IMenu.h"
#include "GameObject.h"

class MenuScene;

class MenuExtra final : public IMenu
{
public:
	MenuExtra(MenuScene& managerScene);
	~MenuExtra();

	void Initialize() {};
	void Draw() const override;
	void Update() override;

	void MoveUp();
	void MoveDown();
	void SelectMenu();
private:
	MenuScene& m_ManagerScene;
	Vector2f m_SelectorPos;
	std::shared_ptr<GameObject> m_pSelector, m_pBgExtraMain, m_pBqExtraMainTxt;
	int m_Index;
	bool m_IsBack;
};

