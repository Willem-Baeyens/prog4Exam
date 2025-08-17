#ifndef BLINKY_CONTROLLER_H
#define BLINKY_CONTROLLER_H

#include "GhostController.h"
class BlinkyController : public GhostController
{
public:
	explicit BlinkyController(PacmanMovement* pacman, GameObject* owner);

private:
	virtual void ChaseTarget();
};
#endif //BLINKY_CONTROLLER_H

