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
	MultiEvent<>* GetPacmanDiesEvent();


private:
	void OnOverlap(CollisionRect* collider);
	MultiEvent<> m_PacmanEatsPellet{};
	MultiEvent<> m_PacmanDies{};

};
#endif //PACMAN_CONTROLLER_H


