#include "Transform.h"


void Transform::SetWorldPosition(const float x, const float y, const float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void Transform::SetWorldPosition(const glm::vec3& position)
{
	m_WorldPosition = position;
}

void Transform::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void Transform::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
}
