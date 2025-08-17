#include "ChangeDirection.h"
#include "GameObject.h"
#include "PacmanMovement.h"

ChangeDirection::ChangeDirection(GameObject* gameObject, const TilePos& direction):
	GameObjectCommand(gameObject),m_PacmanMovementPtr{gameObject->GetComponent<PacmanMovement>()},m_Direction{direction}
{
	assert(m_PacmanMovementPtr);
}

void ChangeDirection::Execute()
{
	m_PacmanMovementPtr->TryTurn(m_Direction);
}
