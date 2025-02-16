#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include "Transform.h"
#include "Component.h"	



class GameObject final
{
public:
	GameObject() = default;
	~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render() const;


	template<class ComponentType, class... Args>
		requires std::derived_from<ComponentType, Component>
	void AddComponent(Args&&... args)
	{
		m_Components.push_back(std::make_unique<ComponentType>(std::forward<Args>(args)...,this));
	}

	template<class ComponentType>
		requires std::derived_from<ComponentType, Component>
	ComponentType* GetComponent()  const
	{
		for (const auto& component : m_Components)
		{
			ComponentType* result{ dynamic_cast<ComponentType*>(component.get()) };
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}

	template<class ComponentType>
		requires std::derived_from<ComponentType, Component>
	bool IsComponentAdded() const
	{
		for (const auto& component : m_Components)
		{
			ComponentType* result{ dynamic_cast<ComponentType*>(component.get()) };
			if (result != nullptr)
			{
				return true;
			}
		}
		return false;
	}

	template<class ComponentType>
		requires std::derived_from<ComponentType, Component>
	void RemoveComponent()
	{
		RemoveComponent(GetComponent<ComponentType>());
	}

	void RemoveComponent(Component* componentToRemove);

	Transform m_Transform{};
private:
	void DeleteComponents();
	std::vector<std::unique_ptr<Component>> m_Components{};
};



