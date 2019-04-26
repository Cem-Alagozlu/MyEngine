#include "MiniginPCH.h"
#include "CommandManager.h"


CommandManager::CommandManager()
{
	InsertCommands();
}


CommandManager::~CommandManager()
{
}

void CommandManager::InsertCommands()
{	//map01
	m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonUP,InputTriggerState::Pressed}, InputCommands::increment });
	m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonDown,InputTriggerState::Pressed}, InputCommands::decrement });
	m_ButtonInputCommands.insert({ myButtonStruct{ControllerButton::ButtonA,InputTriggerState::Pressed}, InputCommands::select });

	//map02
	m_Commands.insert({ InputCommands::increment,Command() });
	m_Commands.insert({ InputCommands::decrement,Command() });
	m_Commands.insert({ InputCommands::select,Command() });
}

void CommandManager::Update()
{
	for (int i = static_cast<int>(ControllerButton::ButtonA); i != static_cast<int>(ControllerButton::ButtonRight); i++)
	{
		ControllerButton button = static_cast<ControllerButton>(i);
		InputTriggerState inputState = InputManager::GetInstance().IsPressed(button);
	
		auto buttonResult = m_ButtonInputCommands.find(myButtonStruct{button,inputState});
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
