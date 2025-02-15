#include "Time.h"

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

float Time::GetFixedDeltaTime() const
{
	return m_FixedDeltaTime;
}

void Time::SetDeltaTime(float deltaTime)
{
	m_DeltaTime = deltaTime;
}
