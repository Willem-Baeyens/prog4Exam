#include <numeric>
#include "Fps.h"
#include "GameObject.h"

Fps::Fps(GameObject* gameObjectPtr):
	m_GameObjectPtr{gameObjectPtr},
	m_Time{Time::GetInstance()},
	m_TextRendererPtr{gameObjectPtr->GetComponent<TextRenderer>()},
	m_DeltaTimes{},
	m_DeltaTimeIndex{0}
{

}

void Fps::Update()
{
	m_DeltaTimes[m_DeltaTimeIndex] = m_Time.GetDeltaTime();

	if (++m_DeltaTimeIndex == m_DeltaTimes.size() - 1)
	{
		const float totalDeltaTime{std::accumulate(m_DeltaTimes.begin(),m_DeltaTimes.end(),0.f)};
		m_TextRendererPtr->SetText("FPS: " + std::to_string(m_DeltaTimes.size()/totalDeltaTime));
		m_DeltaTimeIndex = 0;
	}
}
