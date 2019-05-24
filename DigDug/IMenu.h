#pragma once
namespace cem
{
	class IMenu
	{
	public:
		virtual void Initialize() = 0;
		virtual void Draw() const = 0;
		virtual void Update() = 0;
	};
}