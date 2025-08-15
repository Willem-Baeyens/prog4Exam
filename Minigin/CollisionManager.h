#ifndef COLLLISION_MANAGER_H
#define	COLLLISION_MANAGER_H
class CollisionRect;
struct rect;
namespace CollisionManager
{
	void RegisterRect(CollisionRect* rect);

	void UnregisterRect(CollisionRect* rect);
	void CheckCollisions();

	bool AreOverlapping(const rect& rect1, const rect& rect2);
};
#endif //COLLLISION_MANAGER_H


