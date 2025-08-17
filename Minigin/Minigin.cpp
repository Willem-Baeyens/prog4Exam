#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <thread>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EngineTime.h"
#include "Font.h"
#include "Texture2D.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "CollisionManager.h"

Minigin::Minigin(const std::string& dataPath, int screenWidth, int screenHeight, float renderScale)
{
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment - 2DAE10 Willem Baeyens",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::Initialize(m_Window,renderScale);

	InputManager::Initialize();

	ResourceManager::Initiliaze(dataPath);

	ServiceLocator::RegisterSoundSystem(std::make_unique<SDL_SoundSystem>());

}


Minigin::~Minigin() noexcept
{
	Renderer::Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run(const std::function<void()>& load)
{
	load();

	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	std::chrono::duration<double, std::milli> MaxTimePerFrame{ static_cast<double>(std::milli().den) / static_cast<double>(m_MaxFps) };

	while (m_Continue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		Time::SetDeltaTime(deltaTime);
		lastTime = currentTime;
		lag += deltaTime;

		m_Continue = InputManager::ProcessInput();
		while (lag >= Time::GetFixedDeltaTime())
		{
			SceneManager::FixedUpdate();
			lag -= Time::GetFixedDeltaTime();
		}

		SceneManager::Update();
		CollisionManager::CheckCollisions();
		SceneManager::LateUpdate();
		Renderer::Render();
		const auto sleep_time = MaxTimePerFrame + currentTime - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleep_time);
	}
}

void Minigin::Pause()
{
	m_Continue = false;
}


//TODO
//Rule of 5
//noexcept and nodiscard
//data locality looping over components
//mark classes final
//pimpl SDL
//remove outdated includes
