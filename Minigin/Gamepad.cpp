#include "Gamepad.h"
#include "InputBinding.h"
#include <vector>
#include <algorithm>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "xinput.lib")

class Gamepad::Impl
{
public:
	Impl(int controllerIndex);
	void ProcessInput();

	[[nodiscard]] bool WasPressedThisFrame(int button) const;
	[[nodiscard]] bool WasReleasedThisFrame(int button) const;
	[[nodiscard]] bool IsDown(int button) const;

	void AddBinding(GamepadButton button, std::unique_ptr<Command> command, TriggerType trigger = TriggerType::released);
private:
	int m_ControllerIndex;

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	DWORD m_ButtonsPressedThisFrame{};
	DWORD m_ButtonsReleasedThisFrame{};

	std::vector<InputBinding> m_InputBindingsPressedThisFrame{};
	std::vector<InputBinding> m_InputBindingsReleasedThisFrame{};
	std::vector<InputBinding> m_InputBindingsDown{};
};

Gamepad::Gamepad() = default;

Gamepad::Gamepad(int controllerIndex):
	m_Impl{std::make_unique<Impl>(controllerIndex)}
{
}

Gamepad::~Gamepad() = default;

Gamepad& Gamepad::operator=(Gamepad&& other) noexcept
{
	m_Impl = std::move(other.m_Impl);
	return *this;
}

void Gamepad::ProcessInput()
{
	m_Impl->ProcessInput();
}

[[nodiscard]] bool Gamepad::WasPressedThisFrame(int button) const
{
	return m_Impl->WasPressedThisFrame(button);
}

[[nodiscard]] bool Gamepad::WasReleasedThisFrame(int button) const
{
	return m_Impl->WasReleasedThisFrame(button);
}

[[nodiscard]] bool Gamepad::IsDown(int button) const
{
	return m_Impl->IsDown(button);
}

void Gamepad::AddBinding(GamepadButton button, std::unique_ptr<Command> command, TriggerType trigger)
{
	m_Impl->AddBinding(button, std::move(command), trigger);
}

Gamepad::Impl::Impl(int controllerIndex):
	m_ControllerIndex{controllerIndex}
{
}

void Gamepad::Impl::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonsChanged = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonsChanged & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonsChanged & (~m_CurrentState.Gamepad.wButtons);


	std::ranges::for_each(m_InputBindingsPressedThisFrame, [this](const InputBinding& binding) {
		if (WasPressedThisFrame(binding.button))
		{
			binding.command->Execute();
		}});

	std::ranges::for_each(m_InputBindingsReleasedThisFrame, [this](const InputBinding& binding) {
		if (WasReleasedThisFrame(binding.button))
		{
			binding.command->Execute();
		}});

	std::ranges::for_each(m_InputBindingsDown, [this](const InputBinding& binding) {
		if (IsDown(binding.button))
		{
			binding.command->Execute();
		}});
}

bool Gamepad::Impl::WasPressedThisFrame(int button) const
{
	return button & m_ButtonsPressedThisFrame;
}

bool Gamepad::Impl::WasReleasedThisFrame(int button) const
{
	return button & m_ButtonsReleasedThisFrame;
}

bool Gamepad::Impl::IsDown(int button) const
{
	return button & m_CurrentState.Gamepad.wButtons;
}

void Gamepad::Impl::AddBinding(GamepadButton button, std::unique_ptr<Command> command, TriggerType trigger)
{
	switch (trigger)
	{
	case TriggerType::pressed:
		m_InputBindingsPressedThisFrame.emplace_back(static_cast<int>(button),std::move(command));break;
	case TriggerType::down:
		m_InputBindingsDown.emplace_back(static_cast<int>(button), std::move(command));break;
	case TriggerType::released:
		m_InputBindingsReleasedThisFrame.emplace_back(static_cast<int>(button),std::move(command));break;
	}
}
