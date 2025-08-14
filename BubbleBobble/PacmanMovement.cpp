#include "PacmanMovement.h"
#include "GameObject.h"
#include "EngineTime.h"
#include <iostream>

PacmanMovement::PacmanMovement(glm::vec2 direction, float speed, GameObject* owner):
	m_Direction{direction},m_Speed{speed},Component(owner)
{
	m_OwnerPtr = GetOwner();
}

PacmanMovement::PacmanMovement(GameObject* owner):
	Component(owner)
{
	m_OwnerPtr = GetOwner();
}

void PacmanMovement::Update()
{
	m_OwnerPtr->SetLocalPosition(m_OwnerPtr->GetLocalPosition() + m_Direction * m_Speed * Time::GetDeltaTime());
}

void PacmanMovement::SetDirection(const glm::vec2& direction)
{
	//TODO check if new direction isnt into a wall
	m_Direction = direction;
}
