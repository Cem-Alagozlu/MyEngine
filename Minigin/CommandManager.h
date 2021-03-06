#pragma once
#include "Singleton.h"
#include "Command.h"
#include "InputManager.h"

namespace cem
{
	class CommandManager final : public Singleton<CommandManager>
	{
	public:
		struct myButtonStruct
		{
			ControllerButton controllerButton;
			InputTriggerState inputTriggerState;

			bool operator <(const myButtonStruct &b) const;
		};

		enum class InputCommands
		{
			moveUp,
			moveDown,
			moveLeft,
			moveRight,
			increment,
			decrement,
			pump,
			select

		};



		CommandManager();
		~CommandManager();

		void InsertCommands();
		void Update();
		void AddCallBack(std::function<void()> callBack, InputCommands inputCommands);


	private:
		std::map<InputCommands, Command> m_Commands;
		std::map<myButtonStruct, InputCommands> m_ButtonInputCommands;
	};
}

