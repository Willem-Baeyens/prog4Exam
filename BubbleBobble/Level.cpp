#include "Level.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "Scene.h"
#include "ResourceManager.h" 



Level::Level(const std::filesystem::path& path, Scene* scene, GameObject* player, GameObject* Blinky, GameObject* Pinky, GameObject* Inky, GameObject* Sue)
{
	auto snoep = path;

	m_MazePos = { 0,100 };
	
	auto maze = std::make_unique<GameObject>();
	maze->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("mazeOne.png"));
	maze->SetWorldPosition(m_MazePos);

	scene->Add(std::move(maze));


	std::vector<TilePos> pelletTilePositions{ {1,1},{2,1},{3,1},{4,1} };
	for (const TilePos& pelletTilePos : pelletTilePositions)
	{
		auto pellet = std::make_unique<GameObject>();
		pellet->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("pellet.png"));
		glm::vec2 pelletPos = TilePosToWorldPos(pelletTilePos) + glm::vec2{3,3};
		pellet->SetWorldPosition(pelletPos);
		scene->Add(std::move(pellet));
	}

	player->SetWorldPosition(TilePosToWorldPos({13,16}) + glm::vec2{0,4});
	Blinky->SetWorldPosition(TilePosToWorldPos({13,10}) + glm::vec2{ 0,4 });
	Pinky->SetWorldPosition(TilePosToWorldPos({13,13}) + glm::vec2{ 0,4 });
	Inky->SetWorldPosition(TilePosToWorldPos({11,13}) + glm::vec2{ 0,4 });
	Sue->SetWorldPosition(TilePosToWorldPos({15,13}) + glm::vec2{ 0,4 });

}

glm::vec2 Level::TilePosToWorldPos(TilePos tilePos) const
{
	return m_MazePos + glm::vec2(tilePos.x * 8,tilePos.y * 8);
}




