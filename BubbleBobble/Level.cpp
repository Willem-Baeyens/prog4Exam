#include "Level.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "Scene.h"
#include "ResourceManager.h" 
#include <fstream>
#include <iostream>
#include "PacmanMovement.h"

Level::Level(const std::filesystem::path& path, Scene* scene, GameObject* player, GameObject* Blinky, GameObject* Pinky, GameObject* Inky, GameObject* Sue)
{

	m_MazePos = { 0,100 };

	auto maze = std::make_unique<GameObject>();
	maze->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("mazeOne.png"));
	maze->SetWorldPosition(m_MazePos);

	scene->Add(std::move(maze));


	std::ifstream fs{ path,std::ios::binary | std::ios::in };
	if (!fs.is_open())
		throw new std::runtime_error("Failed to open level file");


	int tileIndex{};
	while (!fs.eof())
	{
		char doubleTile{};
		fs.read(&doubleTile, 1);
		TileType firstTile = static_cast<TileType>(doubleTile >> 4);
		ProcessTile(tileIndex++, firstTile,scene,player,Blinky,Pinky,Inky,Sue);
		TileType secondTile = static_cast<TileType>(doubleTile & 0b00001111);
		ProcessTile(tileIndex++, secondTile,scene,player,Blinky,Pinky,Inky,Sue);
	}

	fs.close();
}

bool Level::IsWall(TilePos tilepos) const
{
	return std::any_of(m_WallTiles.cbegin(), m_WallTiles.cend(), [&tilepos](TilePos element) {return tilepos == element; });
}

void Level::ProcessTile(int tileIndex, TileType type,Scene* scene, GameObject* player, GameObject* Blinky, GameObject* Pinky, GameObject* Inky, GameObject* Sue)
{
	TilePos tilePos{ tileIndex % m_LevelWidth,tileIndex / m_LevelWidth };
	switch (type)
	{
	case TileType::empty:
		break;
	case TileType::pellet:
		CreatePellet(tilePos, scene);
		break;
	case TileType::wall:
		m_WallTiles.push_back(tilePos);
		break;
	case TileType::powerPellet:
		break;
	case TileType::pipe:
		break;
	case TileType::pacman:
		player->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		player->GetComponent<PacmanMovement>()->SetStartPos(tilePos);
		break;
	case TileType::blinky:
		Blinky->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		break;
	case TileType::pinky:
		Pinky->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		break;
	case TileType::inky:
		Inky->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		break;
	case TileType::sue:
		Sue->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		break;
	}
}

void Level::CreatePellet(TilePos tilePos, Scene* scene)
{
	auto pellet = std::make_unique<GameObject>();
	pellet->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("pellet.png"));
	glm::vec2 pelletPos = TilePosToWorldPos(tilePos) + glm::vec2{ 3,3 };
	pellet->SetWorldPosition(pelletPos);
	scene->Add(std::move(pellet));
}

glm::vec2 Level::TilePosToWorldPos(TilePos tilePos) const
{
	return m_MazePos + glm::vec2(tilePos.x * 8,tilePos.y * 8);
}




