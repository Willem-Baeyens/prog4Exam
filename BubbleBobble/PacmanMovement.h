#ifndef PACMANMOVEMENT_H
#define PACMANMOVEMENT_H

#include "Component.h"
#include <glm.hpp>
#include "Level.h"
class CollisionRect;
class SpritesheetRenderer;
class PacmanMovement final : public Component
{
public:
	explicit PacmanMovement(float speed, GameObject* owner);
	explicit PacmanMovement(GameObject* owner);
	virtual void Update() override;
	virtual void Render() override;

	void TryTurn(const TilePos& direction);

	void SetStartPos(TilePos start);

private:
	void Turn(const TilePos& direction);
	void TestOverlap(CollisionRect* collRect);
	void UpdateTargetPosition();


	glm::vec2 m_TargetPosition{ 1,0 };
	float m_Speed{ 30.f };
	GameObject* m_OwnerPtr;
	CollisionRect* m_CollisionRect;
	TilePos m_CurrentTile{};
	TilePos m_TileDirection{};

	TilePos m_StoredTurn{};

	SpritesheetRenderer* m_SpritesheetRenderer{};
};
#endif // !PACMANMOVEMENT_H


