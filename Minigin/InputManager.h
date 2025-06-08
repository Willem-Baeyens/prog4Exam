#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Gamepad.h"
#include <memory>

namespace InputManager
{
	void Initialize();

	bool ProcessInput();

	void AddKeyboardBinding(SDL_Scancode button, std::unique_ptr<Command> command, TriggerType trigger = TriggerType::released);
	void AddGamepadBinding(int controllerID, GamepadButton button, std::unique_ptr<Command> command, TriggerType trigger = TriggerType::released);
}
#endif // !INPUTMANAGER_H
