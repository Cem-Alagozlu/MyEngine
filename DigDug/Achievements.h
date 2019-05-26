#pragma once
#include "Observer.h"
#include "Singleton.h"
#include "Player.h"

namespace cem
{
	class Achievements final : public Observer , public Singleton<Achievements>
	{
	public:
		void Initialize(std::shared_ptr<Player> pPlayer);

		virtual void OnNotify(Events event) override;

	private:
		int m_TotalDigs = 0;
		int m_TotalDugs = 0;
		int m_TotalDeaths = 0;
		int m_TotalFruits = 0;
	};
}
