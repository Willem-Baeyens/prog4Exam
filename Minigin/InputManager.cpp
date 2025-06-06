#include <SDL.h>
#include "InputManager.h"
#include "Command.h"
#include <Windows.h>
#include <Xinput.h>

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

void InputManager::AddCommand(std::unique_ptr<Command> command)
{
	m_Commands.push_back(std::move(command));
}
