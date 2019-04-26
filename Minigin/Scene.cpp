#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Time.h"

//std::move -> efficient transfer -> ref cppreference.com

Scene::Scene(const std::string& name)
	:m_SceneName{std::move(name)}
{
}

void Scene::AddChild(std::shared_ptr<GameObject> gameObject)
{
	m_Objects.push_back(gameObject);
}

void Scene::RootUpdate()
{
	auto deltaTime = Time::GetInstance().GetDeltaTime();

	Update();
	for (auto pObject : m_Objects)
	{
		pObject->Update(deltaTime);
	}
}

void Scene::RootDraw()
{
	Draw();
	for (auto pObject : m_Objects)
	{
		pObject->Draw();
	}
}

void Scene::RootSceneActivated()
{
	SceneActivated();
}

void Scene::RootSceneDeactivated()
{
	SceneDeactivated();
}
