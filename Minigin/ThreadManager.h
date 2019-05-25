#pragma once
#include "Singleton.h"
#include "Thread.h"

namespace cem
{
	class ThreadManager final : public Singleton<ThreadManager>
	{
	public:
		ThreadManager();
		~ThreadManager();

		Thread &GetEnemyThread();

	private:
		Thread m_EnemyThread;
	};
}
