#pragma once
#include "Singleton.h"

class Time final : public Singleton<Time>
{
public:
	float GetDeltaTime() const;
	float GetFixedDeltaTime() const;

	void SetDeltaTime(float deltaTime);
private:
	float m_DeltaTime;
	const float m_FixedDeltaTime{ 1 / 60.f };
};