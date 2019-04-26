#include "MiniginPCH.h"
#include "Command.h"


Command::Command()
{
}


Command::~Command()
{
}

void Command::AddCallBack(std::function<void()> functionCallBack)
{
	m_CallBacks.push_back(functionCallBack);
}

void Command::Execute()
{
	for (size_t i = 0; i < m_CallBacks.size(); i++)
	{
		(m_CallBacks[i])();
	}
}
