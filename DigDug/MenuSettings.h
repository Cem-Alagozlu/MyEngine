#pragma once
#include "IMenu.h"
#include "GameObject.h"
#include "Font.h"
namespace cem
{
	class MenuScene;
	class MenuSettings final : public IMenu
	{
	public:
		MenuSettings(MenuScene& managerScene);
		~MenuSettings();

		void Initialize() {};
		void Draw() const override;
		void Update() override;


		void MoveUp();
		void MoveDown();
		void Select();
		void SetImagesBack();

	private:
		MenuScene& m_ManagerScene;
		std::shared_ptr<cem::GameObject> m_pSelector, m_pBgSettings, m_pMusicText;
		Vector2f m_SelectorPos, m_ScaleAway, m_ScaleNormal;
		int m_Index;
		bool m_IsBack;
	};
}
