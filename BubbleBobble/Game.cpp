#include "Game.h"
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
#include <iostream>
#include "SpritesheetRenderer.h"
#include "PacmanController.h"
#include "ScoreComponent.h"
#include "BlinkyController.h"


namespace Pacman
{
	Minigin* Engine{};
	std::unique_ptr<Level> CurrentLevel{};
	int Score{};

	std::vector<GameObject*> LiveDisplays{};

	void AddLiveDisplay(GameObject* liveDisplay)
	{
		LiveDisplays.push_back(liveDisplay);
	}

	Level* GetCurrentLevel()
	{
		return CurrentLevel.get();
	}

	void SetCurrentLevel(std::unique_ptr<Level> level)
	{
		CurrentLevel = std::move(level);
	}

	void OnPacmanDeath()
	{
		if (LiveDisplays.size() >= 1)
		{
			LiveDisplays.back()->FlagForDeletion();
			LiveDisplays.pop_back();
			CurrentLevel->SoftReset();
		}
		else
		{
			std::cout << "Game Over\n";
			Engine->Pause();
		}
	}

	void BindEvents(PacmanController* pacmanController )
	{
		pacmanController->GetPacmanDiesEvent()->BindFunction(std::bind(OnPacmanDeath));
	}

	void AddEngine(Minigin* engine)
	{
		Engine = engine;
	}

	void LoadGame()
	{
		auto& scene = SceneManager::CreateScene(SDBM_Hash("LevelOne"));

		Font* EmulogicFontPtr = ResourceManager::LoadFont("emulogic.ttf", 8);

		auto msPacman = std::make_unique<GameObject>();
		msPacman->AddComponent<SpritesheetRenderer>(ResourceManager::LoadTexture("msPacmanSheetRight.png"), 4, .1f, false);
		msPacman->SetWorldPosition(0, 100);
		msPacman->AddComponent<CollisionRect>(4.f, 4.f, 12.f, 12.f, ColliderType::pacman);
		msPacman->AddComponent<PacmanMovement>(64.f);
		msPacman->AddComponent<PacmanController>();

		auto score = std::make_unique<GameObject>();
		score->AddComponent<TextRenderer>("1UP 0", EmulogicFontPtr);
		score->AddComponent<ScoreComponent>(msPacman->GetComponent<PacmanController>());
		score->SetWorldPosition(glm::vec2{ 10,90 });

		auto pacmanTurnUp = std::make_unique<ChangeDirection>(msPacman.get(), TilePos{ 0,-1 });
		auto pacmanTurnLeft = std::make_unique<ChangeDirection>(msPacman.get(), TilePos{ -1,0 });
		auto pacmanTurnDown = std::make_unique<ChangeDirection>(msPacman.get(), TilePos{ 0,1 });
		auto pacmanTurnRight = std::make_unique<ChangeDirection>(msPacman.get(), TilePos{ 1,0 });

		InputManager::AddKeyboardBinding(SDL_SCANCODE_W, std::move(pacmanTurnUp), TriggerType::down);
		InputManager::AddKeyboardBinding(SDL_SCANCODE_A, std::move(pacmanTurnLeft), TriggerType::down);
		InputManager::AddKeyboardBinding(SDL_SCANCODE_S, std::move(pacmanTurnDown), TriggerType::down);
		InputManager::AddKeyboardBinding(SDL_SCANCODE_D, std::move(pacmanTurnRight), TriggerType::down);

		InputManager::AddGamepadBinding(0, GamepadButton::DPAD_UP, std::move(pacmanTurnUp), TriggerType::down);
		InputManager::AddGamepadBinding(0, GamepadButton::DPAD_LEFT, std::move(pacmanTurnLeft), TriggerType::down);
		InputManager::AddGamepadBinding(0, GamepadButton::DPAD_DOWN, std::move(pacmanTurnDown), TriggerType::down);
		InputManager::AddGamepadBinding(0, GamepadButton::DPAD_RIGHT, std::move(pacmanTurnRight), TriggerType::down);

		auto blinky = std::make_unique<GameObject>();
		blinky->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("blinky.png"));
		blinky->AddComponent<CollisionRect>(0.f, 0.f, 16.f, 16.f, ColliderType::ghost);
		blinky->AddComponent<BlinkyController>(msPacman->GetComponent<PacmanMovement>());

		auto pinky = std::make_unique<GameObject>();
		pinky->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("pinky.png"));

		auto inky = std::make_unique<GameObject>();
		inky->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("inky.png"));

		auto sue = std::make_unique<GameObject>();
		sue->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("sue.png"));

		auto testLevel = std::make_unique<Level>(ResourceManager::GetDataPath() / "levelOne.bin", &scene, msPacman.get(), blinky.get(), pinky.get(), inky.get(), sue.get());
		Pacman::SetCurrentLevel(std::move(testLevel));

		Pacman::BindEvents(msPacman->GetComponent<PacmanController>());

		for (int livedisplayIndex{}; livedisplayIndex < 4; ++livedisplayIndex)
		{
			auto liveDisplay = std::make_unique<GameObject>();
			liveDisplay->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("msPacman.png"));
			liveDisplay->SetWorldPosition({ livedisplayIndex * 16,350 });
			Pacman::AddLiveDisplay(liveDisplay.get());
			scene.Add(std::move(liveDisplay));
		}

		scene.Add(std::move(msPacman));
		scene.Add(std::move(blinky));
		scene.Add(std::move(pinky));
		scene.Add(std::move(inky));
		scene.Add(std::move(sue));
		scene.Add(std::move(score));
	}


}

