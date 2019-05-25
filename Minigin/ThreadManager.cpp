#include "MiniginPCH.h"
#include "ThreadManager.h"

namespace cem
{

	ThreadManager::ThreadManager()
	{
	}


	ThreadManager::~ThreadManager()
	{
	}

	Thread& ThreadManager::GetEnemyThread()
	{
		return m_EnemyThread;
	}
}
