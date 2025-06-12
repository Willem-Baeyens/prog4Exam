#include <numeric>
#include "Fps.h"
#include "GameObject.h"
#include <sstream>
#include <iomanip>

Fps::Fps(GameObject* ownerPtr):
	Component(ownerPtr),
	m_TextRendererPtr{ownerPtr->GetComponent<TextRenderer>()},
	m_DeltaTimes{},
	m_DeltaTimeIndex{0}
{
	assert(m_TextRendererPtr != nullptr);
}

void Fps::Update()
{
	assert(m_TextRendererPtr);

	m_DeltaTimes[m_DeltaTimeIndex] = Time::GetDeltaTime();

	if (++m_DeltaTimeIndex == m_DeltaTimes.size() - 1)
	{
		const float totalDeltaTime{std::accumulate(m_DeltaTimes.begin(),m_DeltaTimes.end(),0.f)};
		std::stringstream fpsStream;
		fpsStream << std::fixed << std::setprecision(1) << static_cast<float>(m_DeltaTimes.size())/totalDeltaTime;
		
		m_TextRendererPtr->SetText("FPS: " + fpsStream.str());
		m_DeltaTimeIndex = 0;
	}
}
