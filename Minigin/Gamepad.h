#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include "InputBinding.h"
#include <vector>

#pragma comment(lib, "xinput.lib")
class Gamepad
{
public:
	Gamepad(DWORD controllerIndex);

	void ProcessInput();

	bool WasPressedThisFrame(unsigned int button) const;
	bool WasReleasedThisFrame(unsigned int button) const;
	bool IsDown(unsigned int button) const;

	void AddBinding(int button, std::unique_ptr<Command> command, TriggerType trigger = TriggerType::released);
private:
	DWORD m_ControllerIndex;

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	DWORD m_ButtonsPressedThisFrame{};
	DWORD m_ButtonsReleasedThisFrame{};


	std::vector<InputBinding> m_InputBindingsPressedThisFrame{};
	std::vector<InputBinding> m_InputBindingsReleasedThisFrame{};
	std::vector<InputBinding> m_InputBindingsDown{};
};