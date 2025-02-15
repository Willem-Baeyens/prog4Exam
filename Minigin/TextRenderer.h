#pragma once
#include <string>
#include <memory>
#include "Component.h"

class GameObject;
class Font;
class Texture2D;
class TextRenderer final: public Component
{
public:
	TextRenderer(const std::string& text, Font* fontPtr, GameObject* gameObjectPtr);

	virtual void Render() const override;

	void SetText(const std::string& text);
private:
	void UpdateTexture();

	std::string					m_Text;
	GameObject*					m_GameObjectPtr;
	Font*						m_FontPtr;
	std::unique_ptr<Texture2D>	m_TextTexture;
};