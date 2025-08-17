#ifndef COLLISION_RECT_H
#define COLLISION_RECT_H

#include "Component.h"
#include <SDl_pixels.h>
#include "Event.h"
#include <glm.hpp>
#include "rect.h"


class CollisionRect : public Component
{
public:
	explicit CollisionRect(float left, float top, float right, float bottom, GameObject* owner);
	virtual ~CollisionRect();

	virtual void Render() override;

	void MoveRect(const glm::vec2& movement);

	rect GetRect() const;

	MultiEvent<CollisionRect*>* GetOverlapEvent();
	void BroadcastOverlap(); 
private:
	rect m_Rect;

	MultiEvent<CollisionRect*> m_OnOverlap{};

	static const SDL_Color m_DebugDrawColor;
};
#endif // !COLLISION_RECT_H
