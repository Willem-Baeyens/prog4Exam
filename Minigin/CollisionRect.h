#ifndef COLLISION_RECT_H
#define COLLISION_RECT_H

#include "Component.h"
#include <SDl_pixels.h>
#include "Event.h"
#include <glm.hpp>
#include "rect.h"

enum class ColliderType
{
	null,
	pacman,
	pellet,
	powerPellet,
	ghost
};


class CollisionRect : public Component
{
public:
	explicit CollisionRect(float left, float top, float right, float bottom, ColliderType type, GameObject* owner);
	virtual ~CollisionRect();

	virtual void Render() override;

	void MoveRect(const glm::vec2& movement);

	rect GetRect() const;
	ColliderType GetType() const;

	MultiEvent<CollisionRect*>* GetOverlapEvent();
	void BroadcastOverlap(CollisionRect* collider); 
private:
	rect m_Rect;
	ColliderType m_Type{ ColliderType::null };

	MultiEvent<CollisionRect*> m_OnOverlap{};

	static const SDL_Color m_DebugDrawColor;
};
#endif // !COLLISION_RECT_H
