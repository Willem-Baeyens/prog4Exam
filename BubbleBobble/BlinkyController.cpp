#include "BlinkyController.h"
#include "PacmanMovement.h"

BlinkyController::BlinkyController(PacmanMovement* pacman, GameObject* owner):
	GhostController(pacman,owner)
{
}

void BlinkyController::ChaseTarget()
{
	SetTargetTile(GetPacmanMovement()->GetCurrentTile());
}
