#ifndef PACMAN_CONTROLLER_H
#define PACMAN_CONTROLLER_H
#include "Component.h"
#include "Event.h"
class CollisionRect;
class PacmanController final : public Component
{
public:
	explicit PacmanController(GameObject* owner);

	MultiEvent<>* GetPacmanEatsPelletEvent();

private:
	void OnOverlap(CollisionRect* collider);
	MultiEvent<> m_PacmanEatsPellet{};

};
#endif //PACMAN_CONTROLLER_H


