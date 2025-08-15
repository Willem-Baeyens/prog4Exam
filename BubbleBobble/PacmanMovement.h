#ifndef PACMANMOVEMENT_H
#define PACMANMOVEMENT_H

#include "Component.h"
#include <glm.hpp>
class CollisionRect;
class PacmanMovement final : public Component
{
public:
	explicit PacmanMovement(glm::vec2 direction, float speed, GameObject* owner);
	explicit PacmanMovement(GameObject* owner);
	virtual void Update() override;

	void Turn(const glm::vec2& direction);
private:
	void TestOverlap(CollisionRect* collisionRect);

	glm::vec2 m_Direction{ 1,0 };
	float m_Speed{ 30.f };
	GameObject* m_OwnerPtr;
	CollisionRect* m_CollisionRect;
	int test{ 0 };
};
#endif // !PACMANMOVEMENT_H


