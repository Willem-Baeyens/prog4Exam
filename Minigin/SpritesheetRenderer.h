#ifndef SPRITESHEET_RENDERER_H
#define SPRITESHEET_RENDERER_H
#include "Component.h"
#include <sdl.h>

class Texture2D;
class SpritesheetRenderer final : public Component
{
public:
	explicit SpritesheetRenderer(Texture2D* texturePtr, int amountOfFrames, float frameCooldown, GameObject* ownerPtr);
	explicit SpritesheetRenderer(Texture2D* texturePtr, int amountOfFrames, float frameCooldown, bool IsPlaying, GameObject* ownerPtr);


	void Update() override;
	void Render() override;

	void ChangeTexture(Texture2D* texturePtr);

	void SetPlaying(bool isPlaying);
private:
	void NextFrame();

	Texture2D* m_TexturePtr{};
	int m_FrameIndex{};
	int m_AmountOfFrames{};
	float m_FrameCooldown{};
	float m_SecondsSinceLastFrame{};
	int m_FrameWidth{};
	SDL_Rect m_SrcRect{};
	bool m_IsPlaying{false};
};
#endif // !SPRITESHEET_RENDERER_H



