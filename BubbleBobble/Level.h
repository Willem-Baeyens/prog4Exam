#ifndef LEVEL_H
#define LEVEL_H
#include <filesystem>
#include <glm.hpp>
class Scene;
class GameObject;

struct TilePos
{
	int x, y;
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

private:
	[[nodiscard]] glm::vec2 TilePosToWorldPos(TilePos tilePos) const;

	glm::vec2 m_MazePos{};
};
#endif // !LEVEL_H



