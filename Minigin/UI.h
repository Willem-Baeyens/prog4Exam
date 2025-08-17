#ifndef UI_H
#define UI_H
#include <SDL_events.h>
#include <vector>
#include "rect.h"
#include <memory>
#include "Event.h"
#include "Component.h"

class Button final
{
public:
	Button(const rect& rect);

	void Trigger();

	bool IsInRect(int x, int y);

	void BindToTrigger(const std::function<void()>& function);
private:
	rect m_Rect{};
	MultiEvent<> m_TriggerEvent;
};

class UI final
{
public:
	explicit UI() = default;

	void AddButton(std::unique_ptr<Button> button);

	void OnMouseButtonUp(const SDL_MouseButtonEvent& event);
	void OnMouseButtonDown(const SDL_MouseButtonEvent& event);
	void OnMouseMotion(const SDL_MouseMotionEvent& event);

private:
	std::vector<std::unique_ptr<Button>> m_Buttons{};
};
#endif // !UI_H



