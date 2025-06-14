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

Minigin::Minigin(const std::string &dataPath)
{
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment - 2DAE10 Willem Baeyens",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::Initialize(m_Window);

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

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	std::chrono::duration<double, std::milli> MaxTimePerFrame{ static_cast<double>(std::milli().den) / static_cast<double>(m_MaxFps) };

	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		Time::SetDeltaTime(deltaTime);
		lastTime = currentTime;
		lag += deltaTime;

		doContinue = InputManager::ProcessInput();
		while (lag >= Time::GetFixedDeltaTime())
		{
			SceneManager::FixedUpdate();
			lag -= Time::GetFixedDeltaTime();
		}

		SceneManager::Update();
		SceneManager::LateUpdate();
		Renderer::Render();
		const auto sleep_time = MaxTimePerFrame + currentTime - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleep_time);
	}
}


//TODO
//Rule of 5
//noexcept and nodiscard
//data locality looping over components
//mark classes final
//pimpl SDL
//remove outdated includes
