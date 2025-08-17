#ifndef GHOST_CONTROLLER_H
#define GHOST_CONTROLLER_H
#include "Component.h"
#include "Level.h"
#include <glm.hpp>

enum class GhostBehavior
{
	chase,
	scatter,
	frightened,
	eaten
};

class PacmanMovement;
class CollisionRect;
class GhostController  : public Component
{
public: 
	explicit GhostController(PacmanMovement* pacman, GameObject* owner);

	virtual void Update() override;
	virtual void Render() override;

	void SetCurrentTile(TilePos tilePos);
	void SetTargetTile(TilePos tilePos);

	PacmanMovement* GetPacmanMovement() const;

	void SoftReset();
private:
	virtual void ChaseTarget() = 0;
	[[nodiscard]] bool MoveToNextTile();
	void ChooseNewTile();
	int ScorePotentialTile(TilePos tilePos);

	float m_Speed{55.f};
	GhostBehavior m_CurrentBehavior{ GhostBehavior::chase };
	TilePos m_Target{};
	TilePos m_CurrentTile{};
	TilePos m_TileDirection{1,0};
	glm::vec2 m_TargetPosition{};
	TilePos m_LastMove{1,0};
	PacmanMovement* m_Pacman{};
	CollisionRect* m_CollisionRect{};
};
#endif //GHOST_CONTROLLER_H

