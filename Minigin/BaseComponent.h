#pragma once
namespace cem
{
	class GameObject;


	class BaseComponent : public std::enable_shared_from_this<BaseComponent>
	{
		friend GameObject;
	public:
		BaseComponent();
		virtual ~BaseComponent() = default;

		std::shared_ptr<GameObject> GetGameObject();

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	protected:
		std::weak_ptr<GameObject>	m_pGameObject;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() const = 0;

	};
}


