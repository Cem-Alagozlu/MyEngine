#pragma once
#include "Scene.h"
#include "Player.h"

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
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<GameObject> m_pBgLevel;
};

