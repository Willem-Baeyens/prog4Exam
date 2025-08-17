#ifndef CHANGE_DIRECTION_H
#define CHANGE_DIRECTION_H
#include <Command.h>
#include "Level.h"
class ChangeDirection final : public GameObjectCommand
{
public:
	explicit ChangeDirection(GameObject* gameObject, const TilePos& direction);

	virtual void Execute() override;
private:
	class PacmanMovement* m_PacmanMovementPtr{};
	TilePos m_Direction{};
};
#endif // !CHANGE_DIRECTION_H



