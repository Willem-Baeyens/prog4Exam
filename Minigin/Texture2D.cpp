#include <SDL.h>
#include <SDL_image.h>
#include "Texture2D.h"
#include "Renderer.h"
#include <stdexcept>

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

glm::ivec2 Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Texture2D::Texture2D(const std::string &fullPath):
	m_Texture{ IMG_LoadTexture(Renderer::GetSDLRenderer(), fullPath.c_str()) }
{
	if (m_Texture == nullptr)
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
}

Texture2D::Texture2D(SDL_Texture* texture)	: m_Texture{ texture } 
{
	assert(m_Texture != nullptr);
}

