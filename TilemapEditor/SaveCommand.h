#ifndef SAVE_COMMAND_H
#define SAVE_COMMAND_H
#include "Command.h"
class SaveCommand final : public Command
{
public:
	virtual void Execute() override;
};
class LoadCommand final : public Command
{
public:
	virtual void Execute() override;
};
#endif // !SAVE_COMMAND_H
