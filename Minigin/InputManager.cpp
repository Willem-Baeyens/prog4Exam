#include <SDL.h>
#include "InputManager.h"
#include <algorithm>

InputManager::InputManager():
	m_GamePads{{Gamepad(0),Gamepad(1)}}
{
	m_KeysDown.resize(SDL_NUM_SCANCODES, false);
}

bool InputManager::ProcessInput()
{
	SDL_Event e;

	auto bindsButton = [&e](const InputBinding& binding) {return binding.button == e.key.keysym.scancode; };
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

			if (!m_KeysDown[e.key.keysym.scancode])
			{
				auto binding = std::find_if(m_InputBindingsPressedThisFrame.cbegin(), m_InputBindingsPressedThisFrame.cend(), bindsButton);
				if (binding != m_InputBindingsPressedThisFrame.cend())
				{
					binding->command->Execute();
				}

				m_KeysDown[e.key.keysym.scancode] = true;
			}


		}

		if (e.type == SDL_KEYUP)
		{
			auto binding = std::find_if(m_InputBindingsReleasedThisFrame.cbegin(), m_InputBindingsReleasedThisFrame.cend(), bindsButton);
			if (binding != m_InputBindingsReleasedThisFrame.cend())
			{
				binding->command->Execute();
			}

			m_KeysDown[e.key.keysym.scancode] = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
		}
	}

	for (int bindingIndex{}; bindingIndex < m_InputBindingsDown.size(); ++bindingIndex)
	{
		if (m_KeysDown[m_InputBindingsDown[bindingIndex].button])
		{
			m_InputBindingsDown[bindingIndex].command->Execute();
		}
	}

	std::for_each(m_GamePads.begin(), m_GamePads.end(), [](Gamepad& gamepad) {gamepad.ProcessInput(); });


	return true;
}

void InputManager::AddKeyboardBinding(SDL_Scancode button, std::unique_ptr<Command> command, TriggerType trigger)
{
	switch (trigger)
	{
	case TriggerType::pressed:
		m_InputBindingsPressedThisFrame.push_back(InputBinding{button,std::move(command)});
		break;
	case TriggerType::down:
		m_InputBindingsDown.push_back(InputBinding{ button,std::move(command) });
		break;
	case TriggerType::released:
		m_InputBindingsReleasedThisFrame.push_back(InputBinding{ button,std::move(command) });
		break;
	}
}

void InputManager::AddGamepadBinding(GamepadButton button, int controllerID, std::unique_ptr<Command> command, TriggerType trigger)
{
	m_GamePads[controllerID].AddBinding(button, std::move(command), trigger);
}




