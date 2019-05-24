#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace cem
{
	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		virtual void Update(float deltaTime);
		virtual void Draw() const;

		void SetTexture(const std::string& filename);
		void SetPosition(const Vector2f& pos);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return std::dynamic_pointer_cast<T>(component);
			}
			return nullptr;
		}

		void AddComponent(std::shared_ptr<BaseComponent> component);

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

	};
}