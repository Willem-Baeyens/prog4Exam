#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "Command.h"
#include "InputBinding.h"

enum class GamepadButton
{
	DPAD_UP = 0x0001,
	DPAD_DOWN = 0x0002,
	DPAD_LEFT = 0x0004,
	DPAD_RIGHT = 0x0008,
	START = 0x0010,
	BACK = 0x0020,
	LEFT_THUMB = 0x0040,
	RIGHT_THUMB = 0x0080,
	LEFT_SHOULDER = 0x0100,
	RIGHT_SHOULDER = 0x0200,
	A = 0x1000,
	B = 0x2000,
	X = 0x4000,
	Y = 0x8000
};

class Gamepad
{
public:
	Gamepad();
	Gamepad(int controllerIndex);
	~Gamepad();

	Gamepad(const Gamepad& other) = delete;
	Gamepad(Gamepad&& other) = delete;
	Gamepad& operator=(const Gamepad& other) = delete;
	Gamepad& operator=(Gamepad&& other) noexcept;

	void ProcessInput();

	[[nodiscard]] bool WasPressedThisFrame(int button) const;
	[[nodiscard]] bool WasReleasedThisFrame(int button) const;
	[[nodiscard]] bool IsDown(int button) const;

	void AddBinding(GamepadButton button, std::unique_ptr<Command> command, TriggerType trigger = TriggerType::released);
private:
	class Impl;
	std::unique_ptr<Impl> m_Impl;
};
#endif // !GAMEPAD_H
