#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H

#include <string>
#include <memory>
#include "Component.h"

class GameObject;
class Texture2D;
class TextureRenderer final : public Component
{
public:
	TextureRenderer(Texture2D* texturePtr,GameObject* ownerPtr);

	virtual void Render() override;
private:
	Texture2D*	m_TexturePtr;
};
#endif // !TEXTURERENDERER_H