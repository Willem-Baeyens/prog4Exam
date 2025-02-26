#include <string>
#include <algorithm>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


GameObject::GameObject():
	m_Transform{}, m_Components{}, m_Children{}, 
	m_Parent{ nullptr }, m_DeletionFlag{ false }, m_WorldPositionDirty{false}
{
}

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

GameObject* GameObject::GetParent() const
{
	return m_Parent;
}

void GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) or parent == this or m_Parent == parent)
	{
		return;
	}
	if (parent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		}
		SetWorldPositionDirty();
	}
	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

size_t GameObject::GetChildCount() const
{
	return m_Children.size();
}

GameObject* GameObject::GetChildAt(size_t index) const
{
	return m_Children[index];
}

const glm::vec3& GameObject::GetWorldPosition()
{
	if (m_WorldPositionDirty)
	{
		UpdateWorldPosition();
	}
	return m_Transform.GetWorldPosition();
}

void GameObject::SetWorldPosition(float x, float y, float z)
{
	m_Transform.SetWorldPosition(x, y, z);
}

void GameObject::SetWorldPosition(const glm::vec3& position)
{
	m_Transform.SetWorldPosition(position);
}

const glm::vec3& GameObject::GetLocalPosition() const
{
	return m_Transform.GetLocalPosition();
}

void GameObject::SetLocalPosition(float x, float y, float z)
{
	m_Transform.SetLocalPosition(x, y, z);
	SetWorldPositionDirty();
}

void GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_Transform.SetLocalPosition(position);
	SetWorldPositionDirty();
}

void GameObject::SetWorldPositionDirty()
{
	m_WorldPositionDirty = true;
	for (GameObject* child : m_Children)
	{
		child->SetWorldPositionDirty();
	}
}

void GameObject::DeleteComponents()
{
	auto startOfFlaggedComponents{std::partition(m_Components.begin(),m_Components.end(),[](const std::unique_ptr<Component>& component) {return !component->IsFlaggedForDeletion(); })};
	m_Components.erase(startOfFlaggedComponents, m_Components.end());
}

bool GameObject::IsChild(GameObject* object)
{
	return m_Children.cend() != std::find(m_Children.cbegin(), m_Children.cend(), object);
}

void GameObject::RemoveChild(GameObject* object)
{
	std::erase(m_Children, object);
}

void GameObject::AddChild(GameObject* object)
{
	m_Children.push_back(object);
}

void GameObject::UpdateWorldPosition()
{
	if (m_WorldPositionDirty)
	{
		if (m_Parent == nullptr)
		{
			SetWorldPosition(m_Transform.GetLocalPosition());
		}
		else
		{
			SetWorldPosition(m_Parent->GetWorldPosition() + GetLocalPosition());
		}
	}
	m_WorldPositionDirty = false;
}

