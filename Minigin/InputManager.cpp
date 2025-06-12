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
					auto binding = std::ranges::find_if(InputBindingsPressedThisFrame, bindsButton);
					if (binding != InputBindingsPressedThisFrame.cend())
					{
						binding->command->Execute();
					}
		
					KeysDown[e.key.keysym.scancode] = true;
				}
			}
		
			if (e.type == SDL_KEYUP)
			{
				auto binding = std::ranges::find_if(InputBindingsReleasedThisFrame, bindsButton);
				if (binding != InputBindingsReleasedThisFrame.cend())
				{
					binding->command->Execute();
				}
		
				KeysDown[e.key.keysym.scancode] = false;
			}
		}
		

		std::ranges::for_each(InputBindingsDown,
			[](const InputBinding& inputBinding)
			{
				if (KeysDown[inputBinding.button])
				{
					inputBinding.command->Execute();
				}
			});
		
		std::ranges::for_each(GamePads,
			[](Gamepad& gamepad) 
			{
				gamepad.ProcessInput(); 
			});
		
		return true;
	}
	void AddKeyboardBinding(SDL_Scancode button, std::unique_ptr<Command> command, TriggerType trigger)
	{
		switch (trigger)
		{
		case TriggerType::pressed:
			InputBindingsPressedThisFrame.emplace_back(button,std::move(command));
			break;
		case TriggerType::down:
			InputBindingsDown.emplace_back(button,std::move(command));
			break;
		case TriggerType::released:
			InputBindingsReleasedThisFrame.emplace_back(button,std::move(command));
			break;
		}
	}

	void AddGamepadBinding(const int controllerID, GamepadButton button, std::unique_ptr<Command> command, TriggerType trigger)
	{
		GamePads[controllerID].AddBinding(button, std::move(command), trigger);
	}
}



