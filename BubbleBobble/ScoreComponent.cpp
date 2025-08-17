#include "ScoreComponent.h"
#include "GameObject.h"
#include "TextRenderer.h"
#include "PacmanController.h"

ScoreComponent::ScoreComponent(PacmanController* pacmanController, GameObject* owner) :
	Component(owner)
{
	m_TextRenderer = GetOwner()->GetComponent<TextRenderer>();

	pacmanController->GetPacmanEatsPelletEvent()->BindFunction(std::bind(&ScoreComponent::AddScore, this, 10));
}

void ScoreComponent::AddScore(int increase)
{
	m_Score += increase;
	m_TextRenderer->SetText("1UP " + std::to_string(m_Score));
}
