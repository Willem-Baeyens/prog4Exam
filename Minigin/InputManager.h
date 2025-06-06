#pragma once
#include "Singleton.h"
#include "Command.h"
#include <vector>
#include <memory>


class InputManager final : public Singleton<InputManager>
{
public:
	bool ProcessInput();

	void AddCommand(std::unique_ptr<Command> command);

private:
	//Move m_BubbleMove;

	std::vector<std::unique_ptr<Command>> m_Commands;
};
