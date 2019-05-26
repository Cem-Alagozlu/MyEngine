#pragma once
#include "Scene.h"
#include "Player.h"
#include "World.h"
#include "Pooka.h"
#include "PlayerHUD.h"
#include "Fygar.h"
#include "PickUpFruit.h"
#include "Rock.h"

namespace cem
{
	class LevelOne : public Scene
	{
	public:
		LevelOne();
		virtual ~LevelOne() = default;

		LevelOne(const LevelOne& other) = delete;
		LevelOne(LevelOne&& other) noexcept = delete;
		LevelOne& operator=(const LevelOne& other) = delete;
		LevelOne& operator=(LevelOne&& other) noexcept = delete;

	protected:
		void Initialize() override;
		void Update() override;
		void Draw() override;

	private:
		std::shared_ptr<Rock> m_pRock;
		std::shared_ptr<Player> m_pPlayer;
		std::shared_ptr<World> m_pWorld;
		std::vector<std::shared_ptr<Pooka>> m_pPookas;
		std::shared_ptr<Fygar> m_pFygar;
		std::shared_ptr<PlayerHUD> m_pPlayerHUD;
		std::shared_ptr<PickUpFruit> m_pFruits;

		std::shared_ptr<GameObject> m_pLevelOneIMG;
		float m_Timer;
		void LevelSetup();
	};
}
