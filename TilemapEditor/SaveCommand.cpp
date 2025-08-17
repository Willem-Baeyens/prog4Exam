#include "SaveCommand.h"
#include "TilemapEditor.h"
void SaveCommand::Execute()
{
	TilemapEditor::Savemap();
}

void LoadCommand::Execute()
{
	TilemapEditor::Loadmap();
}
