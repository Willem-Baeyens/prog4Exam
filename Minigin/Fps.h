#pragma once
#include <array>
#include "TextRenderer.h"
#include "Time.h"

class GameObject;
class Fps final : public Component
{
public:
	Fps(const GameObject* ownerPtr);

	virtual void Update() override;
private:
	TextRenderer*				m_TextRendererPtr;
	Time&						m_Time;

	std::array<float, 10>		m_DeltaTimes;
	std::size_t					m_DeltaTimeIndex;
};