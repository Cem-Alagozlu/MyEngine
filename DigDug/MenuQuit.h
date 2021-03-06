#pragma once
#include "IMenu.h"
#include "GameObject.h"
namespace cem
{
	class MenuScene;
	class MenuQuit  final : public IMenu
	{
	public:
		MenuQuit(MenuScene& managerScene);
		~MenuQuit();

		void Initialize() {};
		void Draw() const override;
		void Update() override;

		void MoveUp();
		void MoveDown();
		void SelectMenu();
		void SetImagesBack();

	private:
		MenuScene& m_ManagerScene;
		std::shared_ptr<cem::GameObject> m_pSelector, m_pBgQuit, m_pBqQuitTxt;
		Vector2f m_SelectorPos, m_ScaleAway, m_ScaleNormal;
		int m_Index;
		bool m_IsBack;
	};

}