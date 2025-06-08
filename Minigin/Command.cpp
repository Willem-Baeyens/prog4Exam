#include "Command.h"
#include "GameObject.h"
#include "Time.h"

GameObjectCommand::GameObjectCommand(GameObject* gameObject):
	m_GameObject{gameObject}
{
}

GameObject* GameObjectCommand::GetGameObject() const
{
	return m_GameObject;
}

Move::Move(GameObject* gameObject):
	GameObjectCommand(gameObject)
{
}

Move::Move(GameObject* gameObject, glm::vec2 direction, float speed):
	GameObjectCommand{ gameObject },
	m_Direction {glm::normalize(direction)}, 
	m_Speed{ speed }
{
}

void Move::Execute()
{
	glm::vec2 pos = GetGameObject()->GetLocalPosition();
	pos +=  m_Direction * m_Speed * Time::GetDeltaTime();
	GetGameObject()->SetLocalPosition(pos);
}
