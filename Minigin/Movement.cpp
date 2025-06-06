#include "Movement.h"
#include "GameObject.h"
#include "Time.h"

Movement::Movement(GameObject* owner):
	Component(owner)
{
}

void Movement::Update()
{
	glm::vec3 pos{ GetOwner()->GetLocalPosition() };
	pos.x += m_Speed * Time::GetInstance().GetDeltaTime();
	GetOwner()->SetLocalPosition(pos);
}

void Movement::SetSpeed(float speed)
{
	m_Speed = speed;
}
