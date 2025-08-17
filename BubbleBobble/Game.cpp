#include "Game.h"
#include <iostream>
#include "PacmanController.h"

namespace Pacman
{
	std::unique_ptr<Level> CurrentLevel{};
	int Score{};
	Level* GetCurrentLevel()
	{
		return CurrentLevel.get();
	}

	void SetCurrentLevel(std::unique_ptr<Level> level)
	{
		CurrentLevel = std::move(level);
	}

	void AddScore(int score)
	{
		Score += score;
		std::cout << Score << "\n";
	}

	void BindEvents(PacmanController* )
	{
		//pacmanController->GetPacmanEatsPelletEvent()->BindFunction(std::bind(AddScore, 10));
	}


}

