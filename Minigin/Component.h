#pragma once
class GameObject;
class Component
{
public:
	Component(const GameObject* ownerPtr);
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Render() const {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void FixedUpdate() {};

	void FlagForDeletion();
	bool IsFlaggedForDeletion() const;

	const GameObject* GetOwner() const;
private:
	bool m_DeletionFlag{ false };
	const GameObject* m_OwnerPtr;
};