#include <glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Rotator.h"
#include "GameObject.h"
#include "EngineTime.h"


Rotator::Rotator(float radius, float secondsPerRotation,GameObject* pivotObject,GameObject* owner):
	Component(owner), 
	m_SecondsPerRotation{secondsPerRotation}
{
	GetOwner()->SetParent(pivotObject,true);
	glm::vec2 localpos{ sqrt(0.5),sqrt(0.5)};
	localpos *= radius;
	GetOwner()->SetLocalPosition(localpos);
}

void Rotator::Update()
{
	constexpr float twoPi{ static_cast<float>(M_PI) * 2.f };
	const float angle{ twoPi * m_SecondsPerRotation * Time::GetDeltaTime() };

	const float cosine{ cos(angle) };
	const float sine{ sin(angle) };

	const glm::mat2x2 rotationMatrix{cosine, -sine,
									 sine  , cosine};
	glm::vec2 vector{ GetOwner()->GetLocalPosition()};
	vector = rotationMatrix * vector;
	GetOwner()->SetLocalPosition(vector);
}
