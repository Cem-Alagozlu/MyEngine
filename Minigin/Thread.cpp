#include "MiniginPCH.h"
#include "Thread.h"

namespace cem
{
	Thread::Thread()
	{
		m_IsRunning = true;
		m_Thread = std::thread(&Thread::Run,this);

	}


	Thread::~Thread()
	{
		//notify = stop with waiting, program can continue
		m_IsRunning = false;
		m_ConVar.notify_all();
		m_Thread.join();
	}

	void Thread::AddTask(std::function<void()> task)
	{	
		// to syncronize data between two threads, 
		// using mutex for this ( lock guard = automagically lock & unlock) aka m-
		//queue (fifo)
		//also using DEQue if you want to prioritize a specific task , you can push front
		std::lock_guard<std::mutex>lock(m_Mutex);
		m_Tasks.push_back(task);
		m_ConVar.notify_all(); // start working again
	}

	void Thread::Wait()
	{
		while (!m_Tasks.empty())
		{
			//wait untill its empty
		}
	}

	void Thread::Run()
	{
		while (m_IsRunning)
		{
			while (!m_Tasks.empty())
			{
				//lock -> because, you can add a new task in front
				m_Mutex.lock();
				std::function<void()>currTask = m_Tasks.front();
				m_Tasks.pop_front();
				m_Mutex.unlock();
				currTask();
			}
			// 100% cpu usage of thread
			// wait untill if
			std::unique_lock<std::mutex> uniqueLock(m_Mutex);
			m_ConVar.wait(uniqueLock, [this]() {return !m_Tasks.empty() || !m_IsRunning; });
		}
	}
}
