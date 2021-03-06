#pragma once

namespace cem
{
	class Command
	{

	public:
		Command();
		~Command();

		void AddCallBack(std::function<void()> functionCallBack);
		void Execute();


	private:
		std::vector<std::function<void()>> m_CallBacks;

	};
}
