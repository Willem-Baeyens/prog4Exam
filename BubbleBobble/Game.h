#ifndef GAME_H
#define GAME_H
#include "Level.h"
namespace Pacman
{
	Level* GetCurrentLevel();
	void SetCurrentLevel(std::unique_ptr<Level> level);
}
#endif //GAME_H