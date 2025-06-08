#ifndef INPUTBINDING_H
#define INPUTBINDING_H

#include <memory>
#include "Command.h"
struct InputBinding
{
	InputBinding(int button, std::unique_ptr<Command> command);

	int button{ 0 };
	std::unique_ptr<Command> command{};
};

enum class TriggerType
{
	pressed,
	down,
	released
};
#endif // !INPUTBINDING_H

