#include "GhostController.h"
#include "Component.h"
#include "PacmanMovement.h"
#include "Renderer.h"
#include <SDL.h>
#include "rect.h"
#include "Game.h"
#include <array>
#include "EngineTime.h"
#include "GameObject.h"
#include <iostream>
#include "CollisionRect.h"

GhostController::GhostController(PacmanMovement* pacman,GameObject* owner):
	Component(owner),m_Pacman{pacman}
{
	m_CollisionRect = GetOwner()->GetComponent<CollisionRect>();
	assert(m_CollisionRect);
}

void GhostController::Update()
{
	switch (m_CurrentBehavior)
	{
	case GhostBehavior::chase:
		if (MoveToNextTile())
		{
			ChaseTarget();
			ChooseNewTile();
		}
		break;
	}
}

void GhostController::Render()
{
	if constexpr (Renderer::DRAWDEBUG)
	{
		Level* level = Pacman::GetCurrentLevel();
		glm::vec2 currentTileWorldPos = level->TilePosToWorldPos(m_CurrentTile);

		Renderer::DrawRect(rect{ m_TargetPosition.x,m_TargetPosition.y,m_TargetPosition.x + 4,m_TargetPosition.y + 4 }, SDL_Color{ 255, 0, 0, 255 });
		//Renderer::DrawRect(rect{ currentTileWorldPos.x,currentTileWorldPos.y,currentTileWorldPos.x + 8,currentTileWorldPos.y + 8 }, SDL_Color{ 200, 50, 0, 255 });
	}
}

void GhostController::SetCurrentTile(TilePos tilePos)
{
	m_CurrentTile = tilePos;
}

void GhostController::SetTargetTile(TilePos tilePos)
{
	m_Target = tilePos;
}

PacmanMovement* GhostController::GetPacmanMovement() const
{
	return m_Pacman;
}

void GhostController::SoftReset()
{
	m_Target = {};
	m_TargetPosition = {};
	m_LastMove = { 1,0 };
	m_TileDirection = { 1,0 };
}


bool GhostController::MoveToNextTile()
{
	m_TargetPosition = Pacman::GetCurrentLevel()->TilePosToWorldPos(m_CurrentTile + m_TileDirection) + glm::vec2{ -4,-4 };

	glm::vec2 movement{ m_TileDirection.x * m_Speed * Time::GetDeltaTime(), m_TileDirection.y * m_Speed * Time::GetDeltaTime() };
	glm::vec2 oldPosition{ GetOwner()->GetLocalPosition() };
	glm::vec2 newPosition{ GetOwner()->GetLocalPosition() + movement };


	bool hasReachedNextTile{ false };
	switch (m_TileDirection.x)
	{
	case -1:
		if (newPosition.x < m_TargetPosition.x)
		{
			hasReachedNextTile = true;
		}
		break;
	case 1:
		if (newPosition.x > m_TargetPosition.x)
		{
			hasReachedNextTile = true;
		}
		break;
	}

	switch (m_TileDirection.y)
	{
	case -1:
		if (newPosition.y < m_TargetPosition.y)
		{
			hasReachedNextTile = true;
		}
		break;
	case 1:
		if (newPosition.y > m_TargetPosition.y)
		{
			hasReachedNextTile = true;
		}
		break;
	}

	if (hasReachedNextTile)
	{
		m_CurrentTile = m_CurrentTile + m_TileDirection;
		newPosition = m_TargetPosition ;
	}
	GetOwner()->SetLocalPosition(newPosition);
	m_CollisionRect->MoveRect(newPosition - oldPosition);
	return(hasReachedNextTile);
}

void GhostController::ChooseNewTile()
{
	TilePos up{ 0,-1 };
	TilePos left{-1,0};
	TilePos down{ 0,1 };
	TilePos right{ 1,0 };
	std::array<int, 4> scores{0,0,0,0};
	scores[0] = ScorePotentialTile(up);
	scores[1] = ScorePotentialTile(left);
	scores[2] = ScorePotentialTile(down);
	scores[3] = ScorePotentialTile(right);

	int lowestIndex = 0;
	int runningLowestScore = INT_MAX;


	for (int index{ 0 }; index < scores.size(); ++index)
	{
		if (scores[index] < runningLowestScore)
		{
			lowestIndex = index;
			runningLowestScore = scores[index];
		}
	}

	switch (lowestIndex)
	{
	case 0:
		m_TileDirection =  up;
		break;
	case 1:
		m_TileDirection =  left;
		break;
	case 2:
		m_TileDirection =  down;
		break;
	case 3:
		m_TileDirection =  right;
		break;
	}
	m_TargetPosition = Pacman::GetCurrentLevel()->TilePosToWorldPos(m_CurrentTile + m_TileDirection) + glm::vec2{ -4,-4 };
	m_LastMove = m_TileDirection;
}

int GhostController::ScorePotentialTile(TilePos tilePos)
{
	if (tilePos == -m_LastMove) return INT_MAX;
	TilePos candidate{ m_CurrentTile + tilePos };
	if (Pacman::GetCurrentLevel()->IsWall(candidate)) return INT_MAX;

	int squareDistance{ (m_Target.x - candidate.x) * (m_Target.x - candidate.x) + (m_Target.y - candidate.y) * (m_Target.y - candidate.y) };

	return squareDistance;
}


