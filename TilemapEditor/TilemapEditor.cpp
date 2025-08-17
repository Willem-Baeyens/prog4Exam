#include "TilemapEditor.h"
#include "TextureRenderer.h"
#include <array>
#include "Level.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>

namespace TilemapEditor
{
	std::array<TileType, 868> TileMapValues{};
	std::array<TextureRenderer*, 868> TileMapDisplays{};

	void OnTilemapButtonPress(int index)
	{
		switch (TileMapValues[index])
		{
		case TileType::empty:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapPellet.png"));
			TileMapValues[index] = TileType::pellet;
			break;
		case TileType::pellet:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapWall.png"));
			TileMapValues[index] = TileType::wall;
			break;
		case TileType::wall:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapPowerPellet.png"));
			TileMapValues[index] = TileType::powerPellet;
			break;
		case TileType::powerPellet:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapPipe.png"));
			TileMapValues[index] = TileType::pipe;
			break;
		case TileType::pipe:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapPacman.png"));
			TileMapValues[index] = TileType::pacman;
			break;
		case TileType::pacman:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapBlinky.png"));
			TileMapValues[index] = TileType::blinky;
			break;
		case TileType::blinky:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapPinky.png"));
			TileMapValues[index] = TileType::pinky;
			break;
		case TileType::pinky:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapInky.png"));
			TileMapValues[index] = TileType::inky;
			break;
		case TileType::inky:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapSue.png"));
			TileMapValues[index] = TileType::sue;
			break;
		case TileType::sue:
			TileMapDisplays[index]->ChangeTexture(ResourceManager::LoadTexture("tilemapEmpty.png"));
			TileMapValues[index] = TileType::empty;
			break;

		}
	}
	void AddTextureRenderer(TextureRenderer* renderer, int index)
	{
		TileMapDisplays[index] = renderer;
	}
	void Savemap()
	{
		auto path = ResourceManager::GetDataPath() / "testlevel.bin";
		std::cout << "saving to file\n";
		std::ofstream fs{ path , std::ios::binary | std::ios::out};
		for (int tileIndex{}; tileIndex < TileMapValues.size(); tileIndex+=2)
		{
			const char doubleTile = (static_cast<char>(TileMapValues[tileIndex]) << 4) | static_cast<char>(TileMapValues[tileIndex + 1]);

			fs.write(&doubleTile, 1);
		}
		fs.close();
	}

	void SetTextures()
	{
		for (int tileIndex{}; tileIndex < TileMapDisplays.size(); ++tileIndex)
		{
			switch (TileMapValues[tileIndex])
			{
			case TileType::empty:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapEmpty.png"));
				break;
			case TileType::pellet:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapPellet.png"));
				break;
			case TileType::wall:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapWall.png"));
				break;
			case TileType::powerPellet:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapPowerPellet.png"));
				break;
			case TileType::pipe:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapPipe.png"));
				break;
			case TileType::pacman:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapPacman.png"));
				break;
			case TileType::blinky:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapBlinky.png"));
				break;
			case TileType::pinky:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapPinky.png"));
				break;
			case TileType::inky:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapInky.png"));
				break;
			case TileType::sue:
				TileMapDisplays[tileIndex]->ChangeTexture(ResourceManager::LoadTexture("tilemapSue.png"));
				break;
			}
		}
	}

	void Loadmap()
	{
		auto path = ResourceManager::GetDataPath() / "testlevel.bin";
		std::cout << "Loading file\n";
		std::ifstream fs{ path, std::ios::binary | std::ios::in };

		for (int tileIndex{}; tileIndex < TileMapValues.size(); tileIndex += 2)
		{
			char doubleTile{};
			fs.read(&doubleTile, 1);
			TileMapValues[tileIndex] = static_cast<TileType>(doubleTile >> 4);
			TileMapValues[tileIndex +1] = static_cast<TileType>(doubleTile & 0b00001111);
		}
		fs.close();
		SetTextures();
	}


}

