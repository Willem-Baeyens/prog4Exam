#include "Component.h"
#include "GameObject.h"

Component::Component(const GameObject* ownerPtr):
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

const GameObject* Component::GetOwner() const
{
	return m_OwnerPtr;
}
