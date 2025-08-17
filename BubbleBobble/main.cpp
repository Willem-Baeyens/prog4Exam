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
#include "Level.h"

void Load()
{
	auto& scene = SceneManager::CreateScene(SDBM_Hash("Demo"));
	
	//Font* LinguaFontPtr = ResourceManager::LoadFont("Lingua.otf", 24);

	auto msPacman = std::make_unique<GameObject>();
	msPacman->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("msPacman.png"));
	msPacman->SetWorldPosition(0, 100);
	msPacman->AddComponent<CollisionRect>(0.f, 100.f, 16.f, 116.f);
	msPacman->AddComponent<PacmanMovement>(glm::vec2{},50.f);

	auto pacmanTurnUp = std::make_unique<ChangeDirection>(msPacman.get(),glm::vec2{0,-1});
	auto pacmanTurnLeft = std::make_unique<ChangeDirection>(msPacman.get(), glm::vec2{ -1,0 });
	auto pacmanTurnDown = std::make_unique<ChangeDirection>(msPacman.get(), glm::vec2{ 0,1 });
	auto pacmanTurnRight = std::make_unique<ChangeDirection>(msPacman.get(), glm::vec2{ 1,0 });

	InputManager::AddKeyboardBinding(SDL_SCANCODE_W, std::move(pacmanTurnUp), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_A, std::move(pacmanTurnLeft), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_S, std::move(pacmanTurnDown), TriggerType::down);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_D, std::move(pacmanTurnRight), TriggerType::down);

	auto blinky = std::make_unique<GameObject>();
	blinky->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("blinky.png"));

	auto pinky = std::make_unique<GameObject>();
	pinky->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("pinky.png"));

	auto inky = std::make_unique<GameObject>();
	inky->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("inky.png"));

	auto sue = std::make_unique<GameObject>();
	sue->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("sue.png"));

	Level testLevel(ResourceManager::GetDataPath(), &scene,msPacman.get(),blinky.get(),pinky.get(),inky.get(),sue.get());

	scene.Add(std::move(msPacman));
	scene.Add(std::move(blinky));
	scene.Add(std::move(pinky));
	scene.Add(std::move(inky));
	scene.Add(std::move(sue));


}

int SDL_main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(Load);
	return 0;
}