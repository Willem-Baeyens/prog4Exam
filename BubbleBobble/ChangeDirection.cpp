#include "ChangeDirection.h"
#include "GameObject.h"
#include "PacmanMovement.h"

ChangeDirection::ChangeDirection(GameObject* gameObject, const glm::vec2& direction):
	GameObjectCommand(gameObject),m_PacmanMovementPtr{gameObject->GetComponent<PacmanMovement>()},m_Direction{glm::normalize(direction)}
{
	assert(m_PacmanMovementPtr);
}

void ChangeDirection::Execute()
{
	m_PacmanMovementPtr->SetDirection(m_Direction);
}
