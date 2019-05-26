#pragma once
#include "Scene.h"
#include "Rock.h"
#include "Pooka.h"
#include "PlayerHUD.h"
#include "PickUpFruit.h"
#include "Fygar.h"

namespace cem
{
	class LevelTwo : public Scene
	{
	public:
		LevelTwo();
		virtual ~LevelTwo() = default;

		LevelTwo(const LevelTwo& other) = delete;
		LevelTwo(LevelTwo&& other) noexcept = delete;
		LevelTwo& operator=(const LevelTwo& other) = delete;
		LevelTwo& operator=(LevelTwo&& other) noexcept = delete;

	protected:
		void Initialize() override;
		void Update() override;
		void Draw() override;

	private:
		std::shared_ptr<Rock> m_pRock;
		std::shared_ptr<Player> m_pPlayer;
		std::shared_ptr<World> m_pWorld;
		std::vector<std::shared_ptr<Pooka>> m_pPookas;
		std::vector<std::shared_ptr<Fygar>> m_pFygars;
		std::shared_ptr<PlayerHUD> m_pPlayerHUD;
		std::shared_ptr<PickUpFruit> m_pFruits;

		std::shared_ptr<GameObject> m_pLevelTwoIMG;
		float m_Timer;
		void LevelSetup();
	};
}
