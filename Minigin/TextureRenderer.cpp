#include "TextureRenderer.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"

TextureRenderer::TextureRenderer(Texture2D* texturePtr, GameObject* ownerPtr):
	TextureRenderer(texturePtr, glm::vec2{},ownerPtr)
{
}

TextureRenderer::TextureRenderer(Texture2D* texturePtr, const glm::vec2& offset, GameObject* ownerPtr) :
	Component(ownerPtr), m_TexturePtr{ texturePtr }, m_Offset{ offset }
{
	assert(m_TexturePtr);
}




void TextureRenderer::ChangeTexture(Texture2D* texturePtr)
{
	if (texturePtr)
	{
		m_TexturePtr = texturePtr;
	}
}

void TextureRenderer::Render()
{
	glm::vec2 pos = GetOwner()->GetWorldPosition();
	pos += m_Offset;
	Renderer::RenderTexture(*m_TexturePtr, pos.x, pos.y);	
}

