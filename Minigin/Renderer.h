#ifndef RENDERER_H
#define RENDERER_H

class Texture2D;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Color;
struct rect;

namespace Renderer
{
	void Initialize(SDL_Window* window);
	void Render();
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y);
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) ;

	void DrawRect(const rect& rect);
	void DrawRect(const rect& rect, const SDL_Color& color);

	SDL_Renderer* GetSDLRenderer();

	const SDL_Color& GetBackgroundColor();
	void SetBackgroundColor(const SDL_Color& color);
}
//TODO make vector of rendercomponents(not pointers) 
#endif // !RENDERER_H

