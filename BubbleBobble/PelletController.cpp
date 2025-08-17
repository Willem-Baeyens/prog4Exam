#include "PelletController.h"
#include "CollisionRect.h"
#include "GameObject.h"

PelletController::PelletController(GameObject* owner):
	Component(owner)
{
	std::function<void(CollisionRect*)> overlapFunction = std::bind(&PelletController::OnOverlap, this, std::placeholders::_1);
	GetOwner()->GetComponent<CollisionRect>()->GetOverlapEvent()->BindFunction(overlapFunction);
}

void PelletController::OnOverlap(CollisionRect* collider)
{
	if (collider->GetType() == ColliderType::pacman)
	{
		GetOwner()->FlagForDeletion();
	}
}
