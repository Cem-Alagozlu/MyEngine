#include "DigDugPCH.h"
#include "Rock.h"
#include "TextureComponent.h"
#include "CollisionComponent.h"
#include "Timing.h"
#include "Pooka.h"
#include "Fygar.h"
#include "PlayerData.h"

namespace cem
{
	Rock::Rock(std::shared_ptr<World> pWorld)
	{
		m_pWorld = pWorld;
	}

	void Rock::OnOverlap(std::shared_ptr<CollisionComponent> rockCollision,
		std::shared_ptr<CollisionComponent> otherCollision)
	{
		if (std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(otherCollision->GetGameObject()))
		{
			PlayerData::GetInstance().AddLives(-1);
			player->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 0.0f,0.0f });
		}

		if (std::shared_ptr<Pooka> pooka = std::dynamic_pointer_cast<Pooka>(otherCollision->GetGameObject()))
		{
			std::cout << "lel u ded\n";
		}

		if (std::shared_ptr<Fygar> fygar = std::dynamic_pointer_cast<Fygar>(otherCollision->GetGameObject()))
		{
			std::cout << "lel u ded\n";
		}
	}

	void Rock::Initialize()
	{
		m_UnstoppableForceOfDOOM = false;
		m_TargetPos = Vector2f{ 260,200.0f };
		m_pRock = std::make_shared<GameObject>();
		m_pRock->AddComponent(std::make_shared<TransformComponent>());
		m_pRock->GetComponent<TransformComponent>()->SetPosition(Vector2f{ 260,200.0f });
		m_pRock->GetComponent<TransformComponent>()->SetScale(Vector2f{ 2.0f,2.0f });
		m_pRock->AddComponent(std::make_shared<CollisionComponent>(CollisionComponent::CollisionType::Dynamic, Rectf(0.0f, 0.0f, 25.0f, 25.0f)));
		m_pRock->AddComponent(std::make_shared<TextureComponent>("../Resources/Environment/Rock.png"));
		m_pRock->GetComponent<CollisionComponent>()->AddCallBack(std::bind(&Rock::OnOverlap, this, std::placeholders::_1, std::placeholders::_2));
	}

	void Rock::Update(float deltaTime)
	{
		GameObject::Update(deltaTime);
		auto tunnels = m_pWorld.lock()->GetTunnels();

		Vector2f pos = m_pRock->GetComponent<TransformComponent>()->GetPosition();

		auto it = std::min_element(tunnels.begin(), tunnels.end(),
			[pos](std::shared_ptr<Tunnel> pTunnel01, std::shared_ptr<Tunnel> pTunnel02)
		{
			float tunnelDistance01 = Distance(pos, pTunnel01->GetComponent<TransformComponent>()->GetPosition());
			float tunnelDistance02 = Distance(pos, pTunnel02->GetComponent<TransformComponent>()->GetPosition());

			return tunnelDistance01 < tunnelDistance02;
		});

		Vector2f closeCurrPos = (*it)->GetComponent<TransformComponent>()->GetPosition();

		

		auto itDown = std::find_if(tunnels.begin(), tunnels.end(),
			[closeCurrPos](std::shared_ptr<Tunnel> otherTunnel)
		{
			Vector2f newTunnelPos = Vector2f{ closeCurrPos.x , closeCurrPos.y + 32.0f };
			if (newTunnelPos == otherTunnel->GetComponent<TransformComponent>()->GetPosition())
			{
				return true;
			}
			return false;
		});

		if (itDown != tunnels.end() && (*itDown)->GetComponent<TextureComponent>()->GetVisibility())
		{
			m_TargetPos = (*itDown)->GetComponent<TransformComponent>()->GetPosition();
			m_UnstoppableForceOfDOOM = true;
		}

		
		Vector2f normalizeVec = m_TargetPos - pos;
		Normalize(normalizeVec);
		normalizeVec = normalizeVec * Timing::GetInstance().GetDeltaTime() * 1.0f;
		m_pRock->GetComponent<TransformComponent>()->SetPosition(normalizeVec + pos);
	}

	void Rock::Draw() const
	{
		GameObject::Draw();
		m_pRock->Draw();
	}
}
