#ifndef PACMANMOVEMENT_H
#define PACMANMOVEMENT_H

#include "Component.h"
#include <glm.hpp>
class PacmanMovement final : public Component
{
public:
	explicit PacmanMovement(glm::vec2 direction, float speed, GameObject* owner);
	explicit PacmanMovement(GameObject* owner);
	virtual void Update() override;

	void SetDirection(const glm::vec2& direction);
private:
	glm::vec2 m_Direction{ 1,0 };
	float m_Speed{ 30.f };
	GameObject* m_OwnerPtr;
	int test{ 0 };
};
#endif // !PACMANMOVEMENT_H


