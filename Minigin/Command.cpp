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

void Move::Execute()
{
	glm::vec3 pos = GetGameObject()->GetLocalPosition();
	pos +=  m_Direction * m_Speed * Time::GetInstance().GetDeltaTime();
	GetGameObject()->SetLocalPosition(pos);
}
