#pragma once
#include "SceneManager.h"
#include "GameObject.h"

//used overlord engine as 'inspiration'

class GameObject;
class Scene
{
	friend SceneManager;
public:
	Scene(const std::string& name);
	
	virtual ~Scene() = default;
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) noexcept = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) noexcept = delete;

	void AddChild(std::shared_ptr<GameObject> gameObject);

protected:
	
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SceneActivated() {}
	virtual void SceneDeactivated() {}

private:
	void RootUpdate();
	void RootDraw();
	void RootSceneActivated();
	void RootSceneDeactivated();

	std::string m_SceneName;
	std::vector<std::shared_ptr<GameObject>> m_Objects{};
};
