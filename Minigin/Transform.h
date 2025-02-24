#pragma once
#include <glm.hpp>


class Transform final
{
public:
	const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
	void SetWorldPosition(float x, float y, float z);
	void SetWorldPosition(const glm::vec3& position);

	const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
	void SetLocalPosition(float x, float y, float z);
	void SetLocalPosition(const glm::vec3& position);
private:
	glm::vec3 m_LocalPosition;
	glm::vec3 m_WorldPosition;
};
