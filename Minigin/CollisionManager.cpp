#include "CollisionManager.h"
#include "CollisionRect.h"
#include <vector>
#include "Event.h"

namespace CollisionManager
{
	std::vector<CollisionRect*> collisionRects{};

	void RegisterRect(CollisionRect*  collisionRect)
	{
		collisionRects.push_back(collisionRect);
	}

	void UnregisterRect(CollisionRect*)
	{
		//collisionRects.erase(std::find(collisionRects.begin(), collisionRects.end(), collisionRect), collisionRects.end());
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
					collRect->BroadcastOverlap();
				}
			}
		}
	}

	bool AreOverlapping(const rect& rect1, const rect& rect2)
	{
		if (rect1.right < rect2.left) return false;
		if (rect1.left > rect2.right) return false;
		if (rect1.bottom < rect2.top) return false;
		if (rect1.top > rect2.bottom) return false;
		return true;
	}

}

