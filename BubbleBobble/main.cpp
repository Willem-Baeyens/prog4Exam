#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "SDL.h"
#include "Minigin.h"
#include "Game.h"

int SDL_main(int, char* []) {
	Minigin engine("../Data/",448,800,2);
	Pacman::AddEngine(&engine);
	engine.Run(Pacman::LoadGame);
	return 0;
}