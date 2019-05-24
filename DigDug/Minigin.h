#pragma once

struct SDL_Window;

namespace cem
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		enum class GameState
		{
			menu,
			game,
			ending
		};


		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		GameState m_GameState;
	};
}