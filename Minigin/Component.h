#pragma once
class Component
{
public:
	virtual ~Component() = default;

	virtual void Render() const {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void FixedUpdate() {};

	void FlagForDeletion();
	bool IsFlaggedForDeletion() const;
private:
	bool m_DeletionFlag{ false };
};
