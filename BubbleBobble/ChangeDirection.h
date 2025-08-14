#ifndef CHANGE_DIRECTION_H
#define CHANGE_DIRECTION_H
#include <Command.h>
class ChangeDirection final : public GameObjectCommand
{
public:
	explicit ChangeDirection(GameObject* gameObject, const glm::vec2& direction);

	virtual void Execute() override;
private:
	class PacmanMovement* m_PacmanMovementPtr{};
	glm::vec2 m_Direction{};
};
#endif // !CHANGE_DIRECTION_H



