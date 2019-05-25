#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

namespace cem
{
	void SceneManager::Update()
	{
		if (m_pNewActiveScene != nullptr)
		{
			//deactivates the current active scene
			if (m_pActiveScene != nullptr)
			{
				m_pActiveScene->RootSceneDeactivated();
			}

			//Set new scene
			m_pActiveScene = m_pNewActiveScene;
			m_pNewActiveScene = nullptr;

			//Active the new scene
			m_pActiveScene->RootSceneActivated();
		}

		if (m_pActiveScene != nullptr)
		{
			m_pActiveScene->RootUpdate();
		}
	}

	void SceneManager::Draw()
	{
		if (m_pActiveScene != nullptr)
		{
			m_pActiveScene->RootDraw();
		}
	}

	void SceneManager::SetActiveGameScene(const std::string & sceneName)
	{
		const auto it = find_if(m_Scenes.begin(), m_Scenes.end(), [sceneName](std::shared_ptr<Scene> pScene)
		{

			return sceneName == pScene->m_SceneName;

		});

		if (it != m_Scenes.end())
		{
			m_pNewActiveScene = *it;
			m_pNewActiveScene->Initialize();
		}

	}

	std::shared_ptr<Scene> SceneManager::GetActiveScene() const
	{
		return m_pActiveScene;
	}

	void SceneManager::CreateScene(std::shared_ptr<Scene> pScene)
	{
		const auto it = find(m_Scenes.begin(), m_Scenes.end(), pScene);

		if (it == m_Scenes.end())
		{
			m_Scenes.push_back(pScene);

			if (m_pActiveScene == nullptr && m_pNewActiveScene == nullptr)
			{
				m_pNewActiveScene = pScene;
				//m_pNewActiveScene->Initialize();
			}
		}
	}
}