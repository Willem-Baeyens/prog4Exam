#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class Component
{
public:
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Render() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void FixedUpdate() {};

	void FlagForDeletion();
	bool IsFlaggedForDeletion() const;

	GameObject* GetOwner() const;

protected:
	explicit Component(GameObject* ownerPtr);

private:
	GameObject* m_OwnerPtr;
	bool m_DeletionFlag{ false };
};
#endif // !COMPONENT_H