#include "Component.h"

void Component::FlagForDeletion()
{
	m_DeletionFlag = true;
}

bool Component::IsFlaggedForDeletion() const
{
	return m_DeletionFlag;
}
