#include "SpritesheetRenderer.h"
#include <glm.hpp>
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "EngineTime.h"

SpritesheetRenderer::SpritesheetRenderer(Texture2D* texturePtr, int amountOfFrames, float frameCooldown, GameObject* ownerPtr) :
	SpritesheetRenderer(texturePtr, amountOfFrames, frameCooldown, true, ownerPtr)
{
}

SpritesheetRenderer::SpritesheetRenderer(Texture2D* texturePtr, int amountOfFrames, float frameCooldown, bool isPlaying, GameObject* ownerPtr):
Component(ownerPtr), m_TexturePtr{ texturePtr }, m_AmountOfFrames{ amountOfFrames },m_FrameCooldown {frameCooldown},m_IsPlaying{isPlaying}
{
	assert(m_TexturePtr);
	auto size = m_TexturePtr->GetSize();
	m_FrameWidth = size.x / m_AmountOfFrames;
	m_SrcRect.w = m_FrameWidth;
	m_SrcRect.h = size.y;
}

void SpritesheetRenderer::Update()
{
	if (!m_IsPlaying) return;
	m_SecondsSinceLastFrame += Time::GetDeltaTime();
	if (m_SecondsSinceLastFrame > m_FrameCooldown)
	{
		m_SecondsSinceLastFrame -= m_FrameCooldown;
		NextFrame();
	}
}

void SpritesheetRenderer::Render()
{
	glm::vec2 pos = GetOwner()->GetWorldPosition();
	Renderer::RenderTexture(*m_TexturePtr, pos.x, pos.y,m_SrcRect);
}

void SpritesheetRenderer::ChangeTexture(Texture2D* texturePtr)
{
	m_TexturePtr = texturePtr;
}

void SpritesheetRenderer::SetPlaying(bool isPlaying)
{
	m_IsPlaying = isPlaying;
}

void SpritesheetRenderer::NextFrame()
{
	++m_FrameIndex;
	if (m_FrameIndex == m_AmountOfFrames) m_FrameIndex = 0;
	m_SrcRect.x = m_FrameWidth * m_FrameIndex;
}
