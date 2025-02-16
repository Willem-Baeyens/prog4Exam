#include <string>
#include <algorithm>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


GameObject::~GameObject() = default;

void GameObject::Update()
{
	for (auto& component : m_Components)
	{
		component->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : m_Components)
	{
		component->LateUpdate();
	}

	DeleteComponents();
}

void GameObject::FixedUpdate()
{
	for (auto& component : m_Components)
	{
		component->FixedUpdate();
	}
}

void GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}
}

void GameObject::RemoveComponent(Component* componentToRemove)
{
	//std::for_each(std::remove_if(m_Components.begin(), m_Components.end(), [componentToRemove](std::unique_ptr<Component> component) {return component.get() == componentToRemove; }),
	//	m_Components.end(), [componentToRemove]() {componentToRemove->FlagForDeletion(); });
	for (const auto& component : m_Components)
	{
		if (component.get() == componentToRemove)
		{
			componentToRemove->FlagForDeletion();
		}
	}
}

void GameObject::DeleteComponents()
{
	auto startOfFlaggedComponents{ std::find_if(m_Components.begin(), m_Components.end(), [](std::unique_ptr<Component>& component) {return component->IsFlaggedForDeletion(); }) };
	m_Components.erase(startOfFlaggedComponents, m_Components.end());
}
