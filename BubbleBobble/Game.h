#ifndef GAME_H
#define GAME_H
#include "Level.h"
class PacmanController;
namespace Pacman
{
	Level* GetCurrentLevel();
	void SetCurrentLevel(std::unique_ptr<Level> level);

	void BindEvents(PacmanController* pacmanController);
}
#endif //GAME_H