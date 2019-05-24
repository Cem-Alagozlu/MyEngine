#pragma once
#include "IMenu.h"
#include "GameObject.h"
namespace cem
{
	class MenuScene;

	class MenuExtra final : public IMenu
	{
	public:
		enum class ExtraState
		{
			Story,
			Information,
			Credits,
			Main
		};

		MenuExtra(MenuScene& managerScene);
		~MenuExtra();

		void Initialize() {};
		void Draw() const override;
		void Update() override;

		void MoveUp();
		void MoveDown();
		void SelectMenu();
		void SetImagesBack();
		void SetOriginPos();
		void SetBackEverything();
	private:
		MenuScene& m_ManagerScene;
		Vector2f m_SelectorPos, m_ScaleAway, m_ScaleNormal;
		std::shared_ptr<cem::GameObject> m_pSelector, m_pBgExtraMain, m_pBgExtraMainTxt, m_pBgStory, m_pBgInformation, m_pBgCredits;
		int m_Index;
		bool m_IsBack, m_IsStory, m_IsInformation, m_IsCredits, m_IsMainExtra;
		ExtraState m_ExtraState;
	};
}

