#include "TextureRenderer.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"

TextureRenderer::TextureRenderer(Texture2D* texturePtr,GameObject* ownerPtr) :
	Component(ownerPtr),
	m_TexturePtr{ texturePtr }
{
}

void TextureRenderer::Render()
{
	if (m_TexturePtr != nullptr)
	{
		const auto& pos = GetOwner()->GetWorldPosition();
		Renderer::RenderTexture(*m_TexturePtr, pos.x, pos.y);
	}
}
