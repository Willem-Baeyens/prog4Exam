#include <SDL.h>
#include "InputManager.h"
#include <algorithm>
#include <vector>
#include <array>

namespace InputManager
{
	static	std::vector<InputBinding> InputBindingsPressedThisFrame{};
	static	std::vector<InputBinding> InputBindingsReleasedThisFrame{};
	static	std::vector<InputBinding> InputBindingsDown{};

	static std::vector<bool> KeysDown{};

	static std::array<Gamepad, 2> GamePads{};

	void Initialize()
	{
		GamePads = { Gamepad(0),Gamepad(1) };
		KeysDown.resize(SDL_NUM_SCANCODES, false);
	}

	bool ProcessInput()
	{
		SDL_Event e;
		
		auto bindsButton = [&e](const InputBinding& binding) {return binding.button == e.key.keysym.scancode; };
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) {

				if (!KeysDown[e.key.keysym.scancode])
				{
					auto binding = std::find_if(InputBindingsPressedThisFrame.cbegin(), InputBindingsPressedThisFrame.cend(), bindsButton);
					if (binding != InputBindingsPressedThisFrame.cend())
					{
						binding->command->Execute();
					}
		
					KeysDown[e.key.keysym.scancode] = true;
				}
			}
		
			if (e.type == SDL_KEYUP)
			{
				auto binding = std::find_if(InputBindingsReleasedThisFrame.cbegin(), InputBindingsReleasedThisFrame.cend(), bindsButton);
				if (binding != InputBindingsReleasedThisFrame.cend())
				{
					binding->command->Execute();
				}
		
				KeysDown[e.key.keysym.scancode] = false;
			}
		}
		
		for (int bindingIndex{}; bindingIndex < InputBindingsDown.size(); ++bindingIndex)
		{
			if (KeysDown[InputBindingsDown[bindingIndex].button])
			{
				InputBindingsDown[bindingIndex].command->Execute();
			}
		}
		
		std::for_each(GamePads.begin(), GamePads.end(), [](Gamepad& gamepad) {gamepad.ProcessInput(); });
		
		return true;
	}
	void AddKeyboardBinding(SDL_Scancode button, std::unique_ptr<Command> command, TriggerType trigger)
	{
		switch (trigger)
		{
		case TriggerType::pressed:
			InputBindingsPressedThisFrame.push_back(InputBinding{ button,std::move(command) });
			break;
		case TriggerType::down:
			InputBindingsDown.push_back(InputBinding{ button,std::move(command) });
			break;
		case TriggerType::released:
			InputBindingsReleasedThisFrame.push_back(InputBinding{ button,std::move(command) });
			break;
		}
	}

	void AddGamepadBinding(int controllerID, GamepadButton button, std::unique_ptr<Command> command, TriggerType trigger)
	{
		GamePads[controllerID].AddBinding(button, std::move(command), trigger);
	}
}



