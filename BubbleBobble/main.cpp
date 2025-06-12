#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>

#include "Minigin.h"
#include "SDBM_Hash.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextRenderer.h"
#include "TextureRenderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "Fps.h"
#include "Rotator.h"
#include "InputManager.h"
#include "GameObject.h"


void Load()
{
	auto& scene = SceneManager::CreateScene(SDBM_Hash("Demo"));
	
	Font* LinguaFontPtr = ResourceManager::LoadFont("Lingua.otf", 24);
	
	auto backGround = std::make_unique<GameObject>();
	backGround->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("background.tga"));
	
	auto daeLogo = std::make_unique<GameObject>();
	daeLogo->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("logo.tga"));
	daeLogo->SetWorldPosition(216, 180);
	
	auto title = std::make_unique<GameObject>();
	title->AddComponent<TextRenderer>("Programming 4 Assignment", LinguaFontPtr);
	title->SetWorldPosition(160, 20);

	auto bubble = std::make_unique<GameObject>();
	bubble->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("bubble.png"));
	
	auto bobble = std::make_unique<GameObject>();
	bobble->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("bobble.png"));
	bobble->SetWorldPosition(50, 100);
	
	auto BubbleMoveUp = std::make_unique<Move>(bubble.get(), glm::vec2{ 0.f,-1.f }, 10.f);
	auto BubbleMoveLeft = std::make_unique<Move>(bubble.get(), glm::vec2{ -1.f,0.f }, 10.f);
	auto BubbleMoveDown = std::make_unique<Move>(bubble.get(), glm::vec2{ 0.f,1.f }, 10.f);
	auto BubbleMoveRight = std::make_unique<Move>(bubble.get(), glm::vec2{ 1.f,0.f }, 10.f);
	
	auto BobbleMoveUp = std::make_unique<Move>(bobble.get(), glm::vec2{ 0.f,-1.f }, 20.f);
	auto BobbleMoveLeft = std::make_unique<Move>(bobble.get(), glm::vec2{ -1.f,0.f }, 20.f);
	auto BobbleMoveDown = std::make_unique<Move>(bobble.get(), glm::vec2{ 0.f,1.f }, 20.f);
	auto BobbleMoveRight = std::make_unique<Move>(bobble.get(), glm::vec2{ 1.f,0.f }, 20.f);
	
	InputManager::AddKeyboardBinding(SDL_SCANCODE_W, std::move(BubbleMoveUp), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_A, std::move(BubbleMoveLeft), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_S, std::move(BubbleMoveDown), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_D, std::move(BubbleMoveRight), TriggerType::down);
	
	InputManager::AddGamepadBinding(0, GamepadButton::DPAD_UP, std::move(BobbleMoveUp), TriggerType::down);
	InputManager::AddGamepadBinding(0, GamepadButton::DPAD_RIGHT, std::move(BobbleMoveRight), TriggerType::down);
	InputManager::AddGamepadBinding(0, GamepadButton::DPAD_DOWN, std::move(BobbleMoveDown), TriggerType::down);
	InputManager::AddGamepadBinding(0, GamepadButton::DPAD_LEFT, std::move(BobbleMoveLeft), TriggerType::down);
	
	auto fpsCounter = std::make_unique<GameObject>();
	fpsCounter->AddComponent<TextRenderer>("", LinguaFontPtr);
	fpsCounter->AddComponent<Fps>();

	scene.Add(std::move(backGround));
	scene.Add(std::move(daeLogo));
	scene.Add(std::move(title));
	scene.Add(std::move(bubble));
	scene.Add(std::move(bobble));
	scene.Add(std::move(fpsCounter));

	using namespace SceneManager;
	
}

int SDL_main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(Load);
	return 0;
}