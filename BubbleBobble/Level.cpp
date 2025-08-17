#include "Level.h"
#include "GameObject.h"
#include "TextureRenderer.h"
#include "Scene.h"
#include "ResourceManager.h" 
#include <fstream>
#include <iostream>
#include "PacmanMovement.h"
#include "CollisionRect.h"
#include "PelletController.h"
#include "BlinkyController.h"

Level::Level(const std::filesystem::path& path, Scene* scene, GameObject* player, GameObject* Blinky, GameObject* Pinky, GameObject* Inky, GameObject* Sue):
	m_Player{player},m_Blinky{Blinky},m_Pinky{Pinky},m_Inky{Inky},m_Sue{Sue}
{

	m_MazePos = { 0,100 };

	auto maze = std::make_unique<GameObject>();
	maze->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("mazeOne.png"));
	maze->SetWorldPosition(m_MazePos);

	scene->Add(std::move(maze));

	m_WallTiles.resize(868, false);

	std::ifstream fs{ path,std::ios::binary | std::ios::in };
	if (!fs.is_open())
		throw new std::runtime_error("Failed to open level file");


	int tileIndex{};
	while (!fs.eof())
	{
		char doubleTile{};
		fs.read(&doubleTile, 1);
		TileType firstTile = static_cast<TileType>(doubleTile >> 4);
		ProcessTile(tileIndex++, firstTile,scene);
		TileType secondTile = static_cast<TileType>(doubleTile & 0b00001111);
		ProcessTile(tileIndex++, secondTile,scene);
	}

	fs.close();
}

bool Level::IsWall(TilePos tilepos) const
{
	return m_WallTiles[tilepos.x + tilepos.y*m_LevelWidth];
}

void Level::SoftReset()
{
	m_Blinky->GetComponent<CollisionRect>()->MoveRect(m_BlinkyPos - m_Blinky->GetWorldPosition());
	m_Blinky->SetWorldPosition(m_BlinkyPos);
	m_Blinky->GetComponent<BlinkyController>()->SoftReset();
	m_Blinky->GetComponent<BlinkyController>()->SetCurrentTile(m_BlinkyTile);

	m_Player->GetComponent<PacmanMovement>()->SoftReset();
	m_Player->GetComponent<CollisionRect>()->MoveRect(m_PlayerPos - m_Player->GetWorldPosition());
	m_Player->SetWorldPosition(m_PlayerPos);
	m_Player->GetComponent<PacmanMovement>()->SetStartPos(m_PlayerTile);

}

void Level::ProcessTile(int tileIndex, TileType type,Scene* scene)
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
		m_WallTiles[tilePos.x + tilePos.y*m_LevelWidth] = true;
		break;
	case TileType::powerPellet:
		break;
	case TileType::pipe:
		break;
	case TileType::pacman:
		m_PlayerPos = TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 };
		m_PlayerTile = tilePos;
		m_Player->SetWorldPosition(m_PlayerPos);
		m_Player->GetComponent<PacmanMovement>()->SetStartPos(tilePos);
		m_Player->GetComponent<CollisionRect>()->MoveRect(m_PlayerPos);
		break;
	case TileType::blinky:
		m_BlinkyPos = TilePosToWorldPos(tilePos) + glm::vec2{ -4,-4 };
		m_BlinkyTile = tilePos;
		m_Blinky->SetWorldPosition(m_BlinkyPos);
		m_Blinky->GetComponent<CollisionRect>()->MoveRect(m_BlinkyPos);
		m_Blinky->GetComponent<BlinkyController>()->SetCurrentTile(tilePos);
		break;
	case TileType::pinky:
		m_Pinky->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		break;
	case TileType::inky:
		m_Inky->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		break;
	case TileType::sue:
		m_Sue->SetWorldPosition(TilePosToWorldPos(tilePos) + glm::vec2{ 0,-4 });
		break;
	}
}

void Level::CreatePellet(TilePos tilePos, Scene* scene)
{
	auto pellet = std::make_unique<GameObject>();
	pellet->AddComponent<TextureRenderer>(ResourceManager::LoadTexture("pellet.png"));
	glm::vec2 pelletPos = TilePosToWorldPos(tilePos) + glm::vec2{ 3,3 };
	pellet->AddComponent<CollisionRect>(pelletPos.x, pelletPos.y, pelletPos.x + 2, pelletPos.y + 2,ColliderType::pellet);
	pellet->AddComponent<PelletController>();
	pellet->SetWorldPosition(pelletPos);
	scene->Add(std::move(pellet));
	++m_PelletsRemaining;
}

glm::vec2 Level::TilePosToWorldPos(TilePos tilePos) const
{
	return m_MazePos + glm::vec2(tilePos.x * 8,tilePos.y * 8);
}




