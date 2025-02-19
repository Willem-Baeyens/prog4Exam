#pragma once
#include <string>
#include <memory>
#include "Component.h"

class GameObject;
class Texture2D;
class TextureRenderer final : public Component
{
public:
	TextureRenderer(Texture2D* texturePtr, const GameObject* ownerPtr);

	virtual void Render() const override;
private:
	Texture2D*	m_TexturePtr;
};