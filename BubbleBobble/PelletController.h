#ifndef PELLET_CONTROLLER_H
#define PELLET_CONTROLLER_H
#include <Component.h>
class CollisionRect;
class PelletController : public Component
{
public:
	explicit PelletController(GameObject* owner);
private:
	void OnOverlap(CollisionRect* collider);
};
#endif //PELLET_CONTROLLER_H

