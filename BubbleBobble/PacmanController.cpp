#include "PacmanController.h"
#include "GameObject.h"
#include "CollisionRect.h"
#include "Game.h"

PacmanController::PacmanController(GameObject* owner):
	Component(owner)
{
	std::function<void(CollisionRect*)> overlapFunction = std::bind(&PacmanController::OnOverlap, this, std::placeholders::_1);

	GetOwner()->GetComponent<CollisionRect>()->GetOverlapEvent()->BindFunction(overlapFunction);
}

MultiEvent<>* PacmanController::GetPacmanEatsPelletEvent()
{
	return &m_PacmanEatsPellet;
}

void PacmanController::OnOverlap(CollisionRect* collider)
{
	switch (collider->GetType())
	{
	case ColliderType::pellet:
		m_PacmanEatsPellet.Broadcast();
		break;
	}
}
