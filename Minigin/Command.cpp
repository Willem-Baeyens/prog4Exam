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

Move::Move(GameObject* gameObject, glm::vec3 direction, float speed):
	GameObjectCommand{ gameObject },
	m_Direction {direction}, 
	m_Speed{ speed }
{
}

void Move::Execute()
{
	glm::vec3 pos = GetGameObject()->GetLocalPosition();
	pos +=  m_Direction * m_Speed * Time::GetInstance().GetDeltaTime();
	GetGameObject()->SetLocalPosition(pos);
}
