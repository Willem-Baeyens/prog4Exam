#ifndef RENDERER_H
#define RENDERER_H

class Texture2D;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Color;

namespace Renderer
{
	void Initialize(SDL_Window* window);
	void Render();
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y);
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) ;

	SDL_Renderer* GetSDLRenderer();

	const SDL_Color& GetBackgroundColor();
	void SetBackgroundColor(const SDL_Color& color);
}
//TODO make vector of rendercomponents(not pointers) 
#endif // !RENDERER_H

