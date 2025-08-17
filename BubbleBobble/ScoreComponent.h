#ifndef SCORE_COMPONENT_H
#define SCORE_COMPONENT_H
#include "Component.h"
class TextRenderer;
class PacmanController;
class ScoreComponent final : public Component
{
public:
	explicit ScoreComponent(PacmanController*  pacmanController,GameObject* owner);

	void AddScore(int increase);
private:
	int m_Score{};
	TextRenderer* m_TextRenderer;
};
#endif //#endif


