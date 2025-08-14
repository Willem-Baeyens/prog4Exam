#include "CollisionRect.h"
#include "Renderer.h"

const SDL_Color CollisionRect::m_DebugDrawColor = { 39,250,0,255 };

CollisionRect::CollisionRect(float top, float left, float bottom, float right,GameObject* owner):
	Component(owner),m_Top{top},m_Left{left},m_Bottom{bottom},m_Right{right}
{
}

void CollisionRect::Render()
{
	Renderer::DrawRect(m_Top, m_Left, m_Bottom, m_Right,m_DebugDrawColor);
}
