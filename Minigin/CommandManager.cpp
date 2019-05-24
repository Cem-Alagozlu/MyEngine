#include "MiniginPCH.h"
#include "CommandManager.h"

namespace cem
{
	CommandManager::CommandManager()
	{
		InsertCommands();
	}


	CommandManager::~CommandManager()
	{
	}

	void CommandManager::InsertCommands()
	{	//-- MAP01 --//
		// -- *MENU* --//
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonUP,InputTriggerState::Pressed}, InputCommands::increment });
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonDown,InputTriggerState::Pressed}, InputCommands::decrement });
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonA,InputTriggerState::Pressed}, InputCommands::select });

		// -- *Player* --//
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonDown,InputTriggerState::Down}, InputCommands::moveDown });
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonUP,InputTriggerState::Down}, InputCommands::moveUp });
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonLeft,InputTriggerState::Down}, InputCommands::moveLeft });
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonRight,InputTriggerState::Down}, InputCommands::moveRight });
		m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonX,InputTriggerState::Pressed}, InputCommands::pump });

		//-- MAP02 --//
		// -- *MENU* --//
		m_Commands.insert({ InputCommands::increment,Command() });
		m_Commands.insert({ InputCommands::decrement,Command() });
		m_Commands.insert({ InputCommands::select,Command() });

		// -- *Player* --//
		m_Commands.insert({ InputCommands::moveUp,Command() });
		m_Commands.insert({ InputCommands::moveDown,Command() });
		m_Commands.insert({ InputCommands::moveLeft,Command() });
		m_Commands.insert({ InputCommands::moveRight,Command() });
		m_Commands.insert({ InputCommands::pump,Command() });
	}

	void CommandManager::Update()
	{
		for (int i = static_cast<int>(ControllerButton::ButtonA); i != static_cast<int>(ControllerButton::_Size); i++)
		{
			ControllerButton button = static_cast<ControllerButton>(i);
			InputTriggerState inputState = InputManager::GetInstance().IsPressed(button);

			auto buttonResult = m_ButtonInputCommands.find(myButtonStruct{ button,inputState });
			if (buttonResult != m_ButtonInputCommands.end())
			{
				auto commandIT = m_Commands.find(buttonResult->second);
				if (commandIT != m_Commands.end())
				{
					Command& command = commandIT->second;
					command.Execute();
				}
			}
		}
	}

	void CommandManager::AddCallBack(std::function<void()> callBack, InputCommands inputCommands)
	{
		auto it = m_Commands.find(inputCommands);

		if (it != m_Commands.end())
		{
			it->second.AddCallBack(callBack);
		}
	}

	bool CommandManager::myButtonStruct::operator<(const myButtonStruct & b) const
	{
		return std::tie(this->controllerButton, this->inputTriggerState) <
			std::tie(b.controllerButton, b.inputTriggerState);
	}

}