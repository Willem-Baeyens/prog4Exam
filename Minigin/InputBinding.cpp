#include "InputBinding.h"
InputBinding::InputBinding(int button, std::unique_ptr<Command> command) :
	button(button), command(std::move(command))
{
}