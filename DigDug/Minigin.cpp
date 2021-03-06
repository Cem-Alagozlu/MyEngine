#include "DigDugPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "CommandManager.h"
#include "MenuScene.h"
#include "PhysicsManager.h"
#include "Timing.h"
#include "ResourceManager.h"
#include "LevelOne.h"
#include "PlayerData.h"
#include "Achievements.h"
#include "ThreadManager.h"

namespace cem
{

	void Minigin::Initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}

		ResourceManager::GetInstance().Init();

		window = SDL_CreateWindow(
			"Programming 4 assignment",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			550,
			700,
			SDL_WINDOW_OPENGL
		);
		if (window == nullptr)
		{
			throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

		Renderer::GetInstance().Init(window);

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
			return;
		}
	}

	void Minigin::LoadGame() const
	{
		SceneManager::GetInstance().CreateScene(std::make_shared<MenuScene>());
		SceneManager::GetInstance().SetActiveGameScene("MenuScene");
	}

	void Minigin::Cleanup()
	{
		Renderer::GetInstance().Destroy();
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();
		Mix_CloseAudio();
	}

	void Minigin::Run()
	{
		Initialize();

		LoadGame();

		{
			auto& playerData = PlayerData::GetInstance();
			auto& threadManager = ThreadManager::GetInstance();
			auto& time = Timing::GetInstance();
			auto& renderer = Renderer::GetInstance();
			auto& sceneManager = SceneManager::GetInstance();
			auto& input = InputManager::GetInstance();
			auto& commandManager = CommandManager::GetInstance();
			auto& physicsManager = PhysicsManager::GetInstance();

			bool doContinue = true;
			time.Initialize();
			playerData.Initialize();

			
			while (doContinue)
			{

					time.Update();
					doContinue = input.ProcessInput();
					commandManager.Update();
					physicsManager.Update();
					sceneManager.Update();
					threadManager.GetEnemyThread().Wait();
					renderer.Draw();
	
			}
		}

		Cleanup();
	}
}
