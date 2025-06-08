#include "Gamepad.h"
#include <algorithm>
Gamepad::Gamepad(DWORD controllerIndex):
	m_ControllerIndex{controllerIndex}
{
}

void Gamepad::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonsChanged = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonsChanged & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonsChanged & (~m_CurrentState.Gamepad.wButtons);


	std::for_each(m_InputBindingsPressedThisFrame.cbegin(), m_InputBindingsPressedThisFrame.cend(), [this](const InputBinding& binding) {
		if (WasPressedThisFrame(binding.button))
		{
			binding.command->Execute();
		}});

	std::for_each(m_InputBindingsReleasedThisFrame.cbegin(), m_InputBindingsReleasedThisFrame.cend(), [this](const InputBinding& binding) {
		if (WasReleasedThisFrame(binding.button))
		{
			binding.command->Execute();
		}});

	std::for_each(m_InputBindingsDown.cbegin(), m_InputBindingsDown.cend(), [this](const InputBinding& binding) {
		if (IsDown(binding.button))
		{
			binding.command->Execute();
		}});

}

bool Gamepad::WasPressedThisFrame(unsigned int button) const
{
	return button & m_ButtonsPressedThisFrame;
}

bool Gamepad::WasReleasedThisFrame(unsigned int button) const
{
	return button & m_ButtonsReleasedThisFrame;
}

bool Gamepad::IsDown(unsigned int button) const
{
	return button & m_CurrentState.Gamepad.wButtons;
}

void Gamepad::AddBinding(int button, std::unique_ptr<Command> command, TriggerType trigger)
{
	switch (trigger)
	{
	case TriggerType::pressed:
		m_InputBindingsPressedThisFrame.push_back(InputBinding{ button,std::move(command) });
		break;
	case TriggerType::down:
		m_InputBindingsDown.push_back(InputBinding{ button,std::move(command) });
		break;
	case TriggerType::released:
		m_InputBindingsReleasedThisFrame.push_back(InputBinding{ button,std::move(command) });
		break;
	}
}
