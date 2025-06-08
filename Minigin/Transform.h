#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>


class Transform final
{
public:
	const glm::vec2& GetWorldPosition() const { return m_WorldPosition; }
	void SetWorldPosition(float x, float y);
	void SetWorldPosition(const glm::vec2& position);

	const glm::vec2& GetLocalPosition() const { return m_LocalPosition; }
	void SetLocalPosition(float x, float y);
	void SetLocalPosition(const glm::vec2& position);
private:
	glm::vec2 m_LocalPosition{};
	glm::vec2 m_WorldPosition{};
};
#endif // !TRANSFORM_H
