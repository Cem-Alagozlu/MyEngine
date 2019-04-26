#pragma once
#include "BaseComponent.h"
#include "TextDrawComponent.h"

class FPSComponent : public BaseComponent
{
public:
	FPSComponent();
	virtual ~FPSComponent() = default;

	float GetFPS() const;

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) noexcept = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
protected:
	void Update(float deltaTime) override;
	void Draw() const override;


private:
	float m_FPS;
};

