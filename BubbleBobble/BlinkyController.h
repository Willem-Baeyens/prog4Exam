#ifndef BLINKY_CONTROLLER_H
#define BLINKY_CONTROLLER_H
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
class BlinkyController final : public Component
{
public: 
	explicit BlinkyController(PacmanMovement* pacman, GameObject* owner);

	virtual void Update() override;
	virtual void Render() override;

	void SetCurrentTile(TilePos tilePos);
private:
	void Chase();
	void MoveToTile(TilePos tilePos);
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
};
#endif //BLINKY_CONTROLLER_H

