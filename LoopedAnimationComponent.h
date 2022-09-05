#pragma once
#include "AnimationComponent.h"

class LAnimationComponent : public AnimationComponent {
public:
	LAnimationComponent(std::string texture, Vector2u imageCount);

	virtual void update(float dt) override;
};