#pragma once
#include "IMenu.h"
#include "GameObject.h"
#include "SpriteComponent.h"
class MenuScene;

class MenuMain final : public IMenu
{
public:
	MenuMain(MenuScene& managerScene);
	~MenuMain();


	void Initialize() override;
	void Draw() const override;
	void Update() override;


	void MoveUp();
	void MoveDown();
	void SetImagesBack();
	void SelectMenu();
private:
	MenuScene& m_ManagerScene;
	std::shared_ptr<GameObject> m_pSelector,m_pBgIMG,m_pBgTxt,m_pSprite;
	Vector2f m_SelectorPos,m_SetBackPos;
	int m_Index;
};

