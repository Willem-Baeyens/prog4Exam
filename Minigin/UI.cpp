#include "UI.h"

void UI::AddButton(std::unique_ptr<Button> button)
{
	m_Buttons.push_back(std::move(button));
}

void UI::OnMouseButtonUp(const SDL_MouseButtonEvent& event)
{
	for (const std::unique_ptr<Button>& button : m_Buttons)
	{
		if (button->IsInRect(event.x, event.y))
		{
			button->Trigger();
		}
	}
}

void UI::OnMouseButtonDown(const SDL_MouseButtonEvent& )
{
}

void UI::OnMouseMotion(const SDL_MouseMotionEvent& )
{
}


Button::Button(const rect& rect):
	m_Rect{rect}
{
}

void Button::Trigger()
{
	m_TriggerEvent.Broadcast();
}

bool Button::IsInRect(int x, int y)
{
	return m_Rect.left <= x and m_Rect.right >= x and m_Rect.bottom >= y and m_Rect.top <= y;
}

void Button::BindToTrigger(const std::function<void()>& function)
{
	m_TriggerEvent.BindFunction(function);
}
