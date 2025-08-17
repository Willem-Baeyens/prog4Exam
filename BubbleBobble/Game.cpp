#include "Game.h"

namespace Pacman
{
	std::unique_ptr<Level> m_CurrentLevel{};
	Level* GetCurrentLevel()
	{
		return m_CurrentLevel.get();
	}

	void SetCurrentLevel(std::unique_ptr<Level> level)
	{
		m_CurrentLevel = std::move(level);
	}
}

