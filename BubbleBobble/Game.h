#ifndef GAME_H
#define GAME_H
#include "Level.h"
class PacmanController;
class Minigin;
namespace Pacman
{
	Level* GetCurrentLevel();
	void SetCurrentLevel(std::unique_ptr<Level> level);
	void AddLiveDisplay(GameObject* liveDisplay);

	void BindEvents(PacmanController* pacmanController);

	void AddEngine(Minigin* engine);
	void LoadGame();
}
#endif //GAME_H