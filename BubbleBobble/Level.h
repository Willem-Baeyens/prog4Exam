#ifndef LEVEL_H
#define LEVEL_H
#include <filesystem>
#include <glm.hpp>
class Scene;
class GameObject;

struct TilePos
{
	int x, y;

	bool operator== (TilePos other)
	{
		return(x == other.x and y == other.y);
	}

	TilePos operator+(TilePos other)
	{
		return TilePos{ x + other.x,y + other.y };
	}

	TilePos operator-() { return TilePos{ -x,-y }; }
};

enum class TileType : char
{
	empty,
	pellet,
	wall,
	powerPellet,
	pipe,
	pacman,
	blinky,
	pinky,
	inky,
	sue,
};

class Level final
{
public:
	explicit Level(const std::filesystem::path& path, Scene* scene,GameObject* player,GameObject* Blinky,GameObject* Pinky,GameObject* Inky, GameObject* Sue);

	[[nodiscard]] glm::vec2 TilePosToWorldPos(TilePos tilePos) const;
	

	[[nodiscard]] bool IsWall(TilePos tilepos) const;
private:
	void ProcessTile(int tileIndex, TileType type, Scene* scene, GameObject* player, GameObject* Blinky, GameObject* Pinky, GameObject* Inky, GameObject* Sue);

	void CreatePellet(TilePos tilePos, Scene* scene);

	const int m_LevelWidth{ 28 };
	int m_PelletsRemaining{};

	glm::vec2 m_MazePos{};

	std::vector<bool> m_WallTiles{};
};
#endif // !LEVEL_H



