#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <SDL.h>
#include "CollisionRect.h"

int static GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}



namespace Renderer
{
	static SDL_Renderer* Renderer{};
	static SDL_Window* Window{};
	static SDL_Color ClearColor{};

	void Initialize(SDL_Window* window)
	{
		Window = window;
		Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
		if (Renderer == nullptr)
		{
			throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
		}
	}

	void Render()
	{
		const auto& color = GetBackgroundColor();
		SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
		SDL_RenderClear(Renderer);
		
		SceneManager::Render();

		SDL_RenderPresent(Renderer);
	}

	void Destroy()
	{
		if (Renderer)
		{
			SDL_DestroyRenderer(Renderer);
			Renderer = nullptr;
		}
	}

	void RenderTexture(const Texture2D& texture, float x, float y)
	{
		SDL_Rect dst{};
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		SDL_RenderCopy(Renderer, texture.GetSDLTexture(), nullptr, &dst);
	}

	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height)
	{
		SDL_Rect dst{};
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		dst.w = static_cast<int>(width);
		dst.h = static_cast<int>(height);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}

	void DrawRect(const rect& rect)
	{
		SDL_FRect SDLrect{ rect.left,rect.top,rect.right - rect.left,rect.bottom - rect.top };
		SDL_RenderDrawRectF(Renderer, &SDLrect);
	}

	void DrawRect(const rect& rect, const SDL_Color& color)
	{
		SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
		DrawRect(rect);
	}

	SDL_Renderer* GetSDLRenderer()
	{
		return Renderer;
	}

	const SDL_Color& GetBackgroundColor()
	{
		return ClearColor;
	}

	void SetBackgroundColor(const SDL_Color& color)
	{
		ClearColor = color;
	}
}

