#include "DigDugPCH.h"
#include "LevelOne.h"
#include "TextureComponent.h"

LevelOne::LevelOne()
	:Scene{"LevelOne"}
{
}



void LevelOne::Initialize()
{
	m_pWorld = std::make_shared<World>();
	AddChild(m_pWorld);
	m_pWorld->Initialize(*this);

	m_pPlayer = std::make_shared<Player>();
	m_pPlayer->Initialize();
	AddChild(m_pPlayer);

	m_pWorld->SetPlayer(m_pPlayer);
}

void LevelOne::Update()
{
}

void LevelOne::Draw()
{
}
