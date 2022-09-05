#pragma once
#include "AnimatedGraphicsComponent.h"
#include "Enums.h"

class CharacterGraphicsComponent : public AnimatedGraphicsComponent {
private:
	Direction m_CurrentDirection;

public:
	CharacterGraphicsComponent(std::shared_ptr<AnimationComponent> animation, std::shared_ptr<TransformComponent> TC);
	
	void faceLeft();
	void faceRight();
};