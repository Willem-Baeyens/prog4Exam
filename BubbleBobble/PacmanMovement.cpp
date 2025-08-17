#include "PacmanMovement.h"
#include "GameObject.h"
#include "EngineTime.h"
#include <iostream>
#include "CollisionRect.h"

PacmanMovement::PacmanMovement(glm::vec2 direction, float speed, GameObject* owner):
	m_Direction{direction},m_Speed{speed},Component(owner)
{
	m_OwnerPtr = GetOwner();
	m_CollisionRect = m_OwnerPtr->GetComponent<CollisionRect>();
	assert(m_CollisionRect);

	std::function<void(CollisionRect*)> overlapFunction = std::bind(&PacmanMovement::TestOverlap, this, std::placeholders::_1);
	m_CollisionRect->GetOverlapEvent()->BindFunction(overlapFunction);
}

PacmanMovement::PacmanMovement(GameObject* owner):
	PacmanMovement(m_Direction,m_Speed,owner)
{
}

void PacmanMovement::Update()
{
	if (m_Direction == glm::vec2(0, 0)) return;
	glm::vec2 movement{ m_Direction * m_Speed * Time::GetDeltaTime() };
	m_OwnerPtr->SetLocalPosition(m_OwnerPtr->GetLocalPosition() + movement);
	m_CollisionRect->MoveRect(movement);
}


void PacmanMovement::Turn(const glm::vec2& direction)
{
	//TODO check if new direction isnt into a wall
	m_Direction = direction;
}

void PacmanMovement::TestOverlap(CollisionRect*)
{

}



