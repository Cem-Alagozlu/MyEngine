#pragma once
#include "Blackboard.h"

namespace cem
{
	class State
	{
	public:
		State() = default;

		virtual void Enter() {}
		virtual void Exit() {}
		virtual void Update() {}

		void Initialize(Blackboard* blackboard);

		void AddTransitionState(State* state);
		virtual bool CanTransition() = 0;
		const std::vector<State*> &GetTransionStates();

		template <typename T>
		T* GetBlackboard();

	private:
		std::vector<State*> m_pStates;
		Blackboard* m_pBlackboard;
	};

	template <typename T>
	T* State::GetBlackboard()
	{
		return static_cast<T*>(m_pBlackboard);
	}
}

//dynamic_cast -> template 


