#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "Time.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include <SDL_mixer.h>
#include "CommandManager.h"


void Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	//HWND windowHandle = GetConsoleWindow();
	//ShowWindow(windowHandle, SW_SHOW);

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

//

//
//gameObject = std::make_shared<GameObject>();
//to = ResourceManager::GetInstance().LoadTexture("logo.png");
//auto transform = std::make_shared<TransformComponent>();
//transform->SetPosition(Vector2f{ 216, 180 });
//gameObject->AddComponent(transform);
//gameObject->AddComponent(to);
//scene.Add(gameObject);
//
//gameObject = std::make_shared<GameObject>();
//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
//auto to1 = std::make_shared<TextDrawComponent>("Programming 4 Assignment", font);
//auto transform1 = std::make_shared<TransformComponent>();
//transform1->SetPosition(Vector2f{ 80, 20 });
//gameObject->AddComponent(transform1);
//gameObject->AddComponent(to1);
//scene.Add(gameObject);
//
//gameObject = std::make_shared<GameObject>();
//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
//auto fpsComponent = std::make_shared<FPSComponent>();
//auto txtComponent = std::make_shared<TextDrawComponent>("", font);
//auto transform2 = std::make_shared<TransformComponent>();
//transform2->SetPosition(Vector2f{ 20, 20 });
//gameObject->AddComponent(transform2);
//gameObject->AddComponent(fpsComponent);
//gameObject->AddComponent(txtComponent);
//scene.Add(gameObject);
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
		auto& time = Time::GetInstance();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& commandManager = CommandManager::GetInstance();

		bool doContinue = true; 
		time.Initialize();

		while (doContinue)
		{
			time.Update();
			doContinue = input.ProcessInput();
			commandManager.Update();
			sceneManager.Update();
			renderer.Draw();
		}
	}

	Cleanup();
}

