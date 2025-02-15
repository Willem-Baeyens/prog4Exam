#include "TextRenderer.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Font.h"
#include <SDL_ttf.h>

#include <iostream>

TextRenderer::TextRenderer(const std::string& text, Font* fontPtr, GameObject* gameObjectPtr):
	m_NeedsUpdate{ true },m_Text {text}, m_FontPtr{ fontPtr },m_GameObjectPtr{ gameObjectPtr },m_TextTexture{nullptr}
{

}

void TextRenderer::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_GameObjectPtr->m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void TextRenderer::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surface = TTF_RenderText_Blended(m_FontPtr->GetFont(), m_Text.c_str(), color);
		if (surface == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surface);
		m_TextTexture = std::make_unique<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}
