#pragma once
class GameObject;

class BaseComponent
{
	friend GameObject;
public:
	BaseComponent();
	virtual ~BaseComponent() = default;


	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

protected:
	std::weak_ptr<GameObject>	m_pGameObject;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	
};


