#pragma once
#include <string>
#include <memory>
#include "Component.h"

class GameObject;
class Texture2D;
class TextureRenderer final : public Component
{
public:
	TextureRenderer(Texture2D* texturePtr, GameObject* gameObjectPtr);

	virtual void Render() const override;
private:
	GameObject* m_GameObjectPtr;
	Texture2D*	m_TexturePtr;
};