#include <glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Rotator.h"
#include "GameObject.h"
#include "Time.h"


Rotator::Rotator(float radius, float secondsPerRotation,GameObject* pivotObject,GameObject* owner):
	Component(owner), 
	m_SecondsPerRotation{secondsPerRotation}
{
	GetOwner()->SetParent(pivotObject,true);
	glm::vec3 localpos{ 1,1,0};
	glm::normalize(localpos);
	localpos *= radius;
	GetOwner()->SetLocalPosition(localpos);
}

void Rotator::Update()
{
	constexpr float twoPi{ static_cast<float>(M_PI) * 2.f };
	const float angle{ twoPi * m_SecondsPerRotation * Time::GetDeltaTime() };

	const float cosine{ cos(angle) };
	const float sine{ sin(angle) };

	const glm::mat3x3 rotationMatrix{ cosine,sine,0,-sine,cosine,0,0,0,1};
	glm::vec3 vector{ GetOwner()->GetLocalPosition()};
	vector = rotationMatrix * vector;
	GetOwner()->SetLocalPosition(vector);
}
