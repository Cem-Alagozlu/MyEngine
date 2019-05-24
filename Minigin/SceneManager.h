#pragma once
#include "Singleton.h"

namespace cem
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(std::shared_ptr<Scene> pScene);

		void Update();
		void Draw();

		void SetActiveGameScene(const std::string& sceneName);
		std::shared_ptr<Scene> GetActiveScene() const;
	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_pActiveScene, m_pNewActiveScene;
	};
}