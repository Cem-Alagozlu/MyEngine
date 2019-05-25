#pragma once
#include <queue>
#include <mutex>

namespace cem
{
	class Thread
	{
	public:
		Thread();
		~Thread();

		void AddTask(std::function<void()> task);
		void Wait();

	private:
		void Run();
		//notify & wait
		std::condition_variable m_ConVar;
		std::mutex m_Mutex;
		std::deque<std::function<void()>> m_Tasks;
		std::thread m_Thread;
		bool m_IsRunning;
	};
}
