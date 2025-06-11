#ifndef ENGINE_TIME_H
#define ENGINE_TIME_H

namespace Time
{
	float GetDeltaTime();
	float GetFixedDeltaTime();

	void  SetDeltaTime(float deltaTime);
}
#endif // !ENGINE_TIME_H