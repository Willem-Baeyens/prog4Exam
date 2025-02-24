#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* ownerPtr):
	m_OwnerPtr{ownerPtr}
{
	assert(m_OwnerPtr != nullptr);
}

void Component::FlagForDeletion()
{
	m_DeletionFlag = true;
}

bool Component::IsFlaggedForDeletion() const
{
	return m_DeletionFlag;
}

GameObject* Component::GetOwner() const
{
	return m_OwnerPtr;
}

