#include "TextureRenderer.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"

TextureRenderer::TextureRenderer(Texture2D* texturePtr, const GameObject* ownerPtr) :
	Component(ownerPtr),
	m_TexturePtr{ texturePtr }
{
}

void TextureRenderer::Render() const
{
	if (m_TexturePtr != nullptr)
	{
		const auto& pos = GetOwner()->m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
	}
}
