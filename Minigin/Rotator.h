#ifndef ROTATOR_H
#define ROTATOR_H

#include "Component.h"
class Rotator : public Component
{
public:
	Rotator(float radius, float SecondsPerRotation,GameObject* pivotObject, GameObject* owner);

	virtual void Update() override;
private:
	float m_SecondsPerRotation;
};
#endif // !ROTATOR_H

