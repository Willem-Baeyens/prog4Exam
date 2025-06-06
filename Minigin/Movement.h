#pragma once
#include "Component.h"
class Movement final : public Component
{
public:
	Movement(GameObject* owner);

	virtual void Update() override;

	void SetSpeed(float speed);
private:
	float m_Speed{ 10.f };
};

