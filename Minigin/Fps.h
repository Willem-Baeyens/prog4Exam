#ifndef FPS_H
#define FPS_H

#include <array>
#include "TextRenderer.h"
#include "EngineTime.h"

class Fps final : public Component
{
public:
	explicit Fps(GameObject* ownerPtr);

	virtual void Update() override;
private:
	TextRenderer*				m_TextRendererPtr;
	std::array<float, 10>		m_DeltaTimes;
	std::size_t					m_DeltaTimeIndex;
};
#endif // !FPS_H