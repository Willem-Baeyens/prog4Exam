#include "PacmanMovement.h"
#include "GameObject.h"
#include "EngineTime.h"
#include "CollisionRect.h"
#include "Game.h"
#include "Renderer.h"
#include "SpritesheetRenderer.h"
#include "ResourceManager.h"

PacmanMovement::PacmanMovement(float speed, GameObject* owner):
	m_Speed{speed},Component(owner)
{
	m_OwnerPtr = GetOwner();
	m_CollisionRect = m_OwnerPtr->GetComponent<CollisionRect>();
	m_SpritesheetRenderer = m_OwnerPtr->GetComponent<SpritesheetRenderer>();
	assert(m_CollisionRect);
	assert(m_SpritesheetRenderer);
}

PacmanMovement::PacmanMovement(GameObject* owner):
	PacmanMovement(m_Speed,owner)
{
}

void PacmanMovement::Update()
{
	if (m_TileDirection == TilePos{ 0,0 }) return;
	glm::vec2 movement{ m_TileDirection.x * m_Speed * Time::GetDeltaTime(), m_TileDirection.y * m_Speed * Time::GetDeltaTime() };
	glm::vec2 oldPosition{ m_OwnerPtr->GetLocalPosition() };
	glm::vec2 newPosition{ m_OwnerPtr->GetLocalPosition() + movement};


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

		if (m_StoredTurn != TilePos{ 0,0 })
		{
			newPosition = m_TargetPosition;
			Turn(m_StoredTurn);
		}

		else
		{
			if (Pacman::GetCurrentLevel()->IsWall(m_CurrentTile + m_TileDirection))
			{
				m_TileDirection = { 0,0 };
				m_SpritesheetRenderer->SetPlaying(false);
			}
			else
			{
				UpdateTargetPosition();
			}
		}
	}

	m_OwnerPtr->SetLocalPosition(newPosition);
	m_CollisionRect->MoveRect(newPosition - oldPosition);
}

void PacmanMovement::Render()
{
	if constexpr (Renderer::DRAWDEBUG)
	{
		//glm::vec2 currentTilePos = Pacman::GetCurrentLevel()->TilePosToWorldPos(m_CurrentTile);
		//Renderer::DrawRect(rect{ currentTilePos.x,currentTilePos.y,currentTilePos.x + 8,currentTilePos.y + 8 }, SDL_Color{ 0,0,255,255 });
		//Renderer::DrawRect(rect{ m_OwnerPtr->GetWorldPosition().x,m_OwnerPtr->GetWorldPosition().y,m_OwnerPtr->GetWorldPosition().x + 8,m_OwnerPtr->GetWorldPosition().y + 8}, SDL_Color{255,255,0,255});
		Renderer::DrawRect(rect{ m_TargetPosition.x,m_TargetPosition.y,m_TargetPosition.x + 4,m_TargetPosition.y + 4 }, SDL_Color{ 255,255,255,255 });
	}
}

void PacmanMovement::TryTurn(const TilePos& direction)
{
	if (m_TileDirection == direction) return;

	bool verticalToHorizontal{ m_TileDirection.y != 0 and direction.y == 0 };
	bool horizontalToVertical{m_TileDirection.x != 0 and direction.x == 0};
	bool currentlyMoving{ m_TileDirection != TilePos{0,0} };

	if (!Pacman::GetCurrentLevel()->IsWall(m_CurrentTile + direction) and ( not currentlyMoving or (not verticalToHorizontal and not horizontalToVertical)))
	{
		Turn(direction); // turn immediately
	}

	else if (!Pacman::GetCurrentLevel()->IsWall(m_CurrentTile + m_TileDirection + direction))
	{


		if ((verticalToHorizontal or horizontalToVertical))//change horizontal <-> vertical
		{
			m_StoredTurn = direction;//store turn until reaching current targettile
			UpdateTargetPosition();
		}
	}
}



void PacmanMovement::SetStartPos(TilePos start)
{
	m_CurrentTile = start;
}

TilePos PacmanMovement::GetCurrentTile() const
{
	return m_CurrentTile;
}

void PacmanMovement::SoftReset()
{
	m_TargetPosition = { 1,0 };
	m_TileDirection = {};
	m_StoredTurn = {};
}


void PacmanMovement::Turn(const TilePos& direction)
{
	m_TileDirection = direction;
	switch (direction.x)
	{
	case 1:
		m_SpritesheetRenderer->ChangeTexture(ResourceManager::LoadTexture("msPacmanSheetRight.png"));
		break;
	case -1:
		m_SpritesheetRenderer->ChangeTexture(ResourceManager::LoadTexture("msPacmanSheetLeft.png"));
		break;
	}

	switch (direction.y)
	{
	case 1:
		m_SpritesheetRenderer->ChangeTexture(ResourceManager::LoadTexture("msPacmanSheetDown.png"));
		break;
	case -1:
		m_SpritesheetRenderer->ChangeTexture(ResourceManager::LoadTexture("msPacmanSheetUp.png"));
		break;
	}

	m_SpritesheetRenderer->SetPlaying(true);
	m_StoredTurn = { 0,0 };
	UpdateTargetPosition();
}


void PacmanMovement::UpdateTargetPosition()
{
	m_TargetPosition = Pacman::GetCurrentLevel()->TilePosToWorldPos(m_CurrentTile + m_TileDirection) + glm::vec2{-4,-4};
}



