#pragma once
#include "GameObject.h"

namespace cem
{
	class PlayerHUD final : public GameObject
	{
	public:
		PlayerHUD();
		~PlayerHUD();

		void Initialize();


	protected:
		virtual void Update(float deltaTime) override;
		void Draw() const;

	private:
		const int m_TotalAchievements{ 6 };
		std::vector<std::shared_ptr<GameObject>> m_pLivesIMG;
		std::vector<std::shared_ptr<GameObject>> m_pAchievments;
		std::shared_ptr<GameObject> m_pScoreTXT,m_pGameOverIMG;

	};
}

