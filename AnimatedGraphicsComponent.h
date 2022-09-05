#pragma once
#include <memory>
#include "AnimationComponent.h"
#include "GraphicsComponent.h"

class AnimatedGraphicsComponent : public GraphicsComponent {
private:
	std::shared_ptr<AnimationComponent> m_Animation;

public:
	AnimatedGraphicsComponent(std::shared_ptr<AnimationComponent> animation, std::shared_ptr<TransformComponent> TC);

	virtual void setState(int state) override;

	virtual void update(float dt) override;
};