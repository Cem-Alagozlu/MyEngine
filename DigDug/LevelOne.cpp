#include "DigDugPCH.h"
#include "LevelOne.h"
#include "TextureComponent.h"

LevelOne::LevelOne()
	:Scene{"LevelOne"}
{
}

void LevelOne::Initialize()
{
	m_pBgLevel = std::make_shared<GameObject>();
	m_pBgLevel->AddComponent(std::make_shared<TextureComponent>("../Resources/Level/bgLevel.png"));
	m_pBgLevel->AddComponent(std::make_shared<TransformComponent>());
	AddChild(m_pBgLevel);

	m_pPlayer = std::make_shared<Player>();
	m_pPlayer->Initialize();
	AddChild(m_pPlayer);


}

void LevelOne::Update()
{
}

void LevelOne::Draw()
{
}
