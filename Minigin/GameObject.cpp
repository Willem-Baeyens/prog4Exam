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

void GameObject::FlagForDeletion()
{
	m_DeletionFlag = true;
}

bool GameObject::IsFlaggedForDeletion() const
{
	return m_DeletionFlag;
}

void GameObject::RemoveComponent(Component* componentToRemove)
{
	if (componentToRemove->GetOwner() == this)
		componentToRemove->FlagForDeletion();
}

void GameObject::DeleteComponents()
{
	auto startOfFlaggedComponents{std::partition(m_Components.begin(),m_Components.end(),[](const std::unique_ptr<Component>& component) {return !component->IsFlaggedForDeletion(); })};
	m_Components.erase(startOfFlaggedComponents, m_Components.end());
}
