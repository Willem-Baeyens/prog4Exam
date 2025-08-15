#include "CollisionRect.h"
#include "Renderer.h"
#include "CollisionManager.h"
#include <iostream>

const SDL_Color CollisionRect::m_DebugDrawColor = { 39,250,0,255 };

CollisionRect::CollisionRect(float left, float top, float right, float bottom,GameObject* owner):
	Component(owner),m_Rect{left,top,right,bottom}
{
	CollisionManager::RegisterRect(this);
}

CollisionRect::~CollisionRect()
{
	CollisionManager::UnregisterRect(this);
}

void CollisionRect::Render()
{
	if constexpr (true)
	{
		Renderer::DrawRect(m_Rect, m_DebugDrawColor);
	}
}

void CollisionRect::MoveRect(const glm::vec2& movement)
{
	m_Rect.top += movement.y;
	m_Rect.bottom += movement.y;
	m_Rect.left += movement.x;
	m_Rect.right += movement.x;
}

rect CollisionRect::GetRect() const
{
	return m_Rect;
}


MultiEvent<CollisionRect*>* CollisionRect::GetOverlapEvent()
{
	return &m_OnOverlap;
}

void CollisionRect::BroadcastOverlap()
{
	m_OnOverlap.Broadcast(this);
}
