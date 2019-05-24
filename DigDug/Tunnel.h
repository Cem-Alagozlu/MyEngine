#pragma once
#include "GameObject.h"
#include "TextureComponent.h"

namespace cem
{
	class Tunnel final : public GameObject
	{
	public:
		Tunnel() = default;
		~Tunnel() = default;

		void Initialize();

	protected:
		virtual void Update(float deltaTime) override;
		virtual void Draw() const override;

	};
}
