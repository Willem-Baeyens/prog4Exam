#include "Time.h"

namespace Time
{
	static float DeltaTime;
	static const float FixedDeltaTime{ 1 / 60.f };


	float GetDeltaTime()
	{
		return DeltaTime;
	}

	float GetFixedDeltaTime()
	{
		return FixedDeltaTime;
	}

	void SetDeltaTime(float deltaTime)
	{
		DeltaTime = deltaTime;
	}

}