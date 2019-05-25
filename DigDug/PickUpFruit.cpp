#include "DigDugPCH.h"
#include "PickUpFruit.h"
#include "TextureComponent.h"
#include "Timing.h"
#include "PlayerData.h"
#include "CollisionComponent.h"
#include "Player.h"

namespace cem
{

	void PickUpFruit::Initialize()
	{
		m_MoveOut = Vector2f{ -500.0f,-500.0f };
		m_RandomSpawnerTime = float(rand() % 5 + 3);


		for (int idx = 0 ; idx < m_TotalFruits; ++idx)
		{
			auto fruit = std::make_shared<GameObject>();
			fruit->AddComponent(std::make_shared<TransformComponent>());
			std::stringstream str;
			str << "../Resources/Environment/Fruits/img (" << idx + 1  << ")" << ".png";
			fruit->AddComponent(std::make_shared<TextureComponent>(str.str()));
			fruit->GetComponent<TransformComponent>()->SetScale(Vector2f{ 2.0f,2.0f });
			fruit->AddComponent(std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Static, Rectf(0.0f, 0.0f, 14.0f, 14.0f)));
			fruit->GetComponent<TransformComponent>()->SetPosition(Vector2f(m_MoveOut));
			fruit->GetComponent<CollisionComponent>()->AddCallBack(std::bind(&PickUpFruit::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));
			m_pFruits.push_back(fruit);
		}
	}

	void PickUpFruit::SetScoreFromFruit()
	{
			 PlayerData::GetInstance().SetScore(50 * m_RandomFruitSelector);
	}

	void PickUpFruit::Respawn()
	{
		m_pFruits[m_RandomFruitSelector]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ m_MoveOut });
		m_RandomFruitSelector = rand() % 11;
		m_RandomSpawnerTime = float(rand() % 5 + 3);
		m_RandomPos.x = float(rand() % 391);
		m_RandomPos.y = float(rand() % 630 + 30);
		m_pFruits[m_RandomFruitSelector]->GetComponent<TransformComponent>()->SetPosition(Vector2f{ m_RandomPos });
	}

	void PickUpFruit::OnOverlap(std::shared_ptr<CollisionComponent> fruitCollision,
		std::shared_ptr<CollisionComponent> otherCollision)
	{
		if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(otherCollision->GetGameObject()))
		{
			SetScoreFromFruit();
			Respawn();
		}
	}

	void PickUpFruit::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
		m_RandomSpawnerTime -= Timing::GetInstance().GetDeltaTime();
		
		if (m_RandomSpawnerTime <= 0.0f)
		{
			
			Respawn();
		}

	}

	void PickUpFruit::Draw() const
	{
		GameObject::Draw();
		m_pFruits[m_RandomFruitSelector]->Draw();
	}
}
