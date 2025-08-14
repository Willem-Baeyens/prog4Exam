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
#include "Font.h"
#include "Fps.h"
#include "Rotator.h"
#include "InputManager.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "PacmanMovement.h"
#include "ChangeDirection.h"
#include "CollisionRect.h"

void Load()
{
	auto& scene = SceneManager::CreateScene(SDBM_Hash("Demo"));
	
	Font* LinguaFontPtr = ResourceManager::LoadFont("Lingua.otf", 24);
	
	auto backGround = std::make_unique<GameObject>();
	backGround->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("background.tga"));

	auto maze = std::make_unique<GameObject>();
	maze->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("mazeOne.png"));
	maze->SetWorldPosition(0, 100);

	auto daeLogo = std::make_unique<GameObject>();
	daeLogo->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("logo.tga"));
	daeLogo->SetWorldPosition(216, 180);
	
	auto title = std::make_unique<GameObject>();
	title->AddComponent<TextRenderer>("Programming 4 Assignment", LinguaFontPtr);
	title->SetWorldPosition(160, 20);

	auto msPacman = std::make_unique<GameObject>();
	msPacman->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("msPacman.png"));
	msPacman->SetWorldPosition(0, 100);
	msPacman->AddComponent<PacmanMovement>(glm::vec2{},50.f);
	msPacman->AddComponent<CollisionRect>(0.f, 100.f, 16.f, 116.f);

	auto fpsCounter = std::make_unique<GameObject>();
	fpsCounter->AddComponent<TextRenderer>("",LinguaFontPtr);
	fpsCounter->AddComponent<Fps>();

	auto pacmanTurnUp = std::make_unique<ChangeDirection>(msPacman.get(),glm::vec2{0,-1});
	auto pacmanTurnLeft = std::make_unique<ChangeDirection>(msPacman.get(), glm::vec2{ -1,0 });
	auto pacmanTurnDown = std::make_unique<ChangeDirection>(msPacman.get(), glm::vec2{ 0,1 });
	auto pacmanTurnRight = std::make_unique<ChangeDirection>(msPacman.get(), glm::vec2{ 1,0 });

	InputManager::AddKeyboardBinding(SDL_SCANCODE_W, std::move(pacmanTurnUp), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_A, std::move(pacmanTurnLeft), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_S, std::move(pacmanTurnDown), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_D, std::move(pacmanTurnRight), TriggerType::down);

	
	//auto BubbleMoveUp = std::make_unique<Move>(bubble.get(), glm::vec2{ 0.f,-1.f }, 10.f);
	//auto BubbleMoveLeft = std::make_unique<Move>(bubble.get(), glm::vec2{ -1.f,0.f }, 10.f);
	//auto BubbleMoveDown = std::make_unique<Move>(bubble.get(), glm::vec2{ 0.f,1.f }, 10.f);
	//auto BubbleMoveRight = std::make_unique<Move>(bubble.get(), glm::vec2{ 1.f,0.f }, 10.f);
	//
	//auto BobbleMoveUp = std::make_unique<Move>(bobble.get(), glm::vec2{ 0.f,-1.f }, 20.f);
	//auto BobbleMoveLeft = std::make_unique<Move>(bobble.get(), glm::vec2{ -1.f,0.f }, 20.f);
	//auto BobbleMoveDown = std::make_unique<Move>(bobble.get(), glm::vec2{ 0.f,1.f }, 20.f);
	//auto BobbleMoveRight = std::make_unique<Move>(bobble.get(), glm::vec2{ 1.f,0.f }, 20.f);
	//
	//InputManager::AddKeyboardBinding(SDL_SCANCODE_W, std::move(BubbleMoveUp), TriggerType::down);
	//InputManager::AddKeyboardBinding(SDL_SCANCODE_A, std::move(BubbleMoveLeft), TriggerType::down);
	//InputManager::AddKeyboardBinding(SDL_SCANCODE_S, std::move(BubbleMoveDown), TriggerType::down);
	//InputManager::AddKeyboardBinding(SDL_SCANCODE_D, std::move(BubbleMoveRight), TriggerType::down);
	//
	//InputManager::AddGamepadBinding(0, GamepadButton::DPAD_UP, std::move(BobbleMoveUp), TriggerType::down);
	//InputManager::AddGamepadBinding(0, GamepadButton::DPAD_RIGHT, std::move(BobbleMoveRight), TriggerType::down);
	//InputManager::AddGamepadBinding(0, GamepadButton::DPAD_DOWN, std::move(BobbleMoveDown), TriggerType::down);
	//InputManager::AddGamepadBinding(0, GamepadButton::DPAD_LEFT, std::move(BobbleMoveLeft), TriggerType::down);
	
	//scene.Add(std::move(backGround));
	//scene.Add(std::move(daeLogo));
	//scene.Add(std::move(title));
	scene.Add(std::move(maze));
	scene.Add(std::move(msPacman));
	scene.Add(std::move(fpsCounter));
}

int SDL_main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(Load);
	return 0;
}