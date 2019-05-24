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
		std::vector<std::shared_ptr<GameObject>> m_pLivesIMG;
		std::shared_ptr<GameObject> m_pScoreTXT;
		int m_TotalLives;
	};
}

