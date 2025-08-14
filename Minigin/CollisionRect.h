#ifndef COLLISION_RECT_H
#define COLLISION_RECT_H

#include "Component.h"
#include <SDl_pixels.h>

class CollisionRect : public Component
{
public:
	explicit CollisionRect(float top, float left, float bottom, float right,GameObject* owner);

	virtual void Render() override;
private:
	float m_Top{}, m_Left{}, m_Bottom{}, m_Right{};
	static const SDL_Color m_DebugDrawColor;
};
#endif // !COLLISION_RECT_H
