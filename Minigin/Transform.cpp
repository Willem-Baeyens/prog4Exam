#include "Transform.h"


void Transform::SetWorldPosition(const float x, const float y)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
}

void Transform::SetWorldPosition(const glm::vec2& position)
{
	m_WorldPosition = position;
}

void Transform::SetLocalPosition(float x, float y)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
}

void Transform::SetLocalPosition(const glm::vec2& position)
{
	m_LocalPosition = position;
}
