#pragma once
#include "Events.h"

namespace cem
{
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(Events event) = 0;
	};
	
}
