#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <string>
#include <memory>
#include "Component.h"
#include "Texture2D.h"

class GameObject;
class Font;
class TextRenderer final: public Component
{
public:
	TextRenderer(std::string text, Font* fontPtr, GameObject* ownerPtr);

	virtual void Render() override;

	void SetText(const std::string& text);
private:
	void UpdateTexture();

	std::string					m_Text;
	Font*						m_FontPtr;
	std::unique_ptr<Texture2D>	m_TextTextureUptr;
};
#endif // !TEXTRENDERER_H