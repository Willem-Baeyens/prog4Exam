#include "CollisionManager.h"
#include "CollisionRect.h"
#include <vector>
#include "Event.h"

namespace CollisionManager
{
	std::vector<CollisionRect*> collisionRects{};

	void RegisterRect(CollisionRect* collisionRect)
	{
		collisionRects.push_back(collisionRect);
	}

	void UnregisterRect(CollisionRect* collisionRect)
	{
		if (collisionRects.empty()) return;
		std::erase(collisionRects, collisionRect);
	}

	void CheckCollisions()
	{
		for (const auto& collRect : collisionRects)
		{
			for (const auto& collRect2 : collisionRects)
			{
				if (collRect == collRect2) continue;
				if (AreOverlapping(collRect->GetRect(), collRect2->GetRect()))
				{
					collRect->BroadcastOverlap(collRect2);
				}
			}
		}
	}

	bool AreOverlapping(const rect& rect1, const rect& rect2)
	{
		return !(rect1.right < rect2.left or rect1.left > rect2.right or rect1.bottom < rect2.top or rect1.top > rect2.bottom);
	}

}

