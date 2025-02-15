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