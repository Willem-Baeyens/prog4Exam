#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include "Transform.h"
#include "Component.h"	

class GameObject final
{
public:
	GameObject();
	~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render() const;

	void FlagForDeletion();
	bool IsFlaggedForDeletion() const;


	template<class ComponentType, class... Args>
		requires std::derived_from<ComponentType, Component>
	void AddComponent(Args&&... args)
	{
		m_Components.emplace_back(std::move(std::make_unique<ComponentType>(std::forward<Args>(args)...,this)));
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
	bool HasComponent() const
	{
		return GetComponent<ComponentType>() != nullptr;
	}

	void RemoveComponent(Component* componentToRemove);

	GameObject* GetParent() const;
	void SetParent(GameObject* parent, bool keepWorldPosition);

	size_t GetChildCount() const;
	GameObject* GetChildAt(size_t index) const;


	const glm::vec2& GetWorldPosition();
	void SetWorldPosition(float x, float y);
	void SetWorldPosition(const glm::vec2& position);

	const glm::vec2& GetLocalPosition() const;
	void SetLocalPosition(float x, float y);
	void SetLocalPosition(const glm::vec2& position);

private:
	void DeleteComponents();

	bool IsChild(GameObject* object);
	void RemoveChild(GameObject* object);
	void AddChild(GameObject* object);

	void SetWorldPositionDirty();
	void UpdateWorldPosition();

	Transform m_Transform;
	std::vector<std::unique_ptr<Component>> m_Components;
	std::vector<GameObject*> m_Children;
	GameObject* m_Parent;
	bool m_DeletionFlag;
	bool m_WorldPositionDirty;
};
#endif // !GAMEOBJECT_H
