#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H

#include <string>
#include <memory>
#include "Component.h"
#include <glm.hpp>


class GameObject;
class Texture2D;
class TextureRenderer final : public Component
{
public:
	explicit TextureRenderer(Texture2D* texturePtr,GameObject* ownerPtr);
	explicit TextureRenderer(Texture2D* texturePtr, const glm::vec2& offset, GameObject* ownerPtr);

	void ChangeTexture(Texture2D* texturePtr);
	void Render() override;
private:
	Texture2D*	m_TexturePtr;
	glm::vec2	m_Offset{};
};
#endif // !TEXTURERENDERER_H