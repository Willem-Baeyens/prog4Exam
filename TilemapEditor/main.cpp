#include "Minigin.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Scene.h"
#include "SDBM_Hash.h"
#include "TextureRenderer.h"
#include "ResourceManager.h"
#include "UI.h"
#include <iostream>
#include <bitset>
#include <array>
#include "InputManager.h"
#include "UIManager.h"
#include "TilemapEditor.h"
#include "SaveCommand.h"



void Load()
{
	auto& scene = SceneManager::CreateScene(SDBM_Hash("Demo"));

	auto maze = std::make_unique<GameObject>();
	maze->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("mazeOne.png"));
	scene.Add(std::move(maze));


	
	size_t editorUIIndex = UIManager::CreateUI();
	UI* editorUI = UIManager::GetUI(editorUIIndex);
	
	for (int buttonIndex{ 0 }; buttonIndex < 868; ++buttonIndex)
	{
		auto tilemapDisplay = std::make_unique<GameObject>();
		int tileX = buttonIndex % 28;
		int tileY = buttonIndex / 28;
		glm::vec2 worldPosition{ tileX * 8,tileY * 8 };
		tilemapDisplay->SetWorldPosition(worldPosition);
		tilemapDisplay->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("tilemapEmpty.png"));

		TilemapEditor::AddTextureRenderer(tilemapDisplay->GetComponent<TextureRenderer>(), buttonIndex);
		auto function = std::bind(TilemapEditor::OnTilemapButtonPress, buttonIndex);

		scene.Add(std::move(tilemapDisplay));

		auto button = std::make_unique<Button>(rect{ worldPosition.x,worldPosition.y,worldPosition.x + 8,worldPosition.y + 8 });
		button->BindToTrigger(function);
		editorUI->AddButton(std::move(button));
	}

	UIManager::SetActiveUI(editorUIIndex);

	auto saveTilemap = std::make_unique<SaveCommand>();
	auto loadTilemap = std::make_unique<LoadCommand>();

	InputManager::AddKeyboardBinding(SDL_SCANCODE_S,std::move(saveTilemap), TriggerType::released);
	InputManager::AddKeyboardBinding(SDL_SCANCODE_L, std::move(loadTilemap), TriggerType::released);

}

int SDL_main(int, char* []) {
	Minigin engine("../Data/",448,496,2);
	engine.Run(Load);
	return 0;
}