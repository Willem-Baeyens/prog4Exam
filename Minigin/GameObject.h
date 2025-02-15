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
	void FixedUpdate();
	void Render() const;


	template<class ComponentType, class... Args>
	void AddComponent(Args&&... args)
	{
		m_Components.push_back(new ComponentType(std::forward<Args>(args)...,this));
	}

	template<class ComponentType>
	ComponentType GetComponent() const
	{
		for (const auto& c : m_Components)
		{
			c;
		}
	}

	Transform m_Transform{};
private:
	std::vector<Component*> m_Components{};
};



