#pragma once
#include "Singleton.h"
#include <array>
#include "Gamepad.h"

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager();

	bool ProcessInput();

	void AddKeyboardBinding(SDL_Scancode button,std::unique_ptr<Command> command, TriggerType trigger = TriggerType::released);
	void AddGamepadBinding(int button, DWORD controllerID, std::unique_ptr<Command> command, TriggerType trigger = TriggerType::released);

private:
	std::vector<InputBinding> m_InputBindingsPressedThisFrame{};
	std::vector<InputBinding> m_InputBindingsReleasedThisFrame{};
	std::vector<InputBinding> m_InputBindingsDown{};

	std::vector<bool> m_KeysDown{};

	std::array<Gamepad, 2> m_GamePads;
};
