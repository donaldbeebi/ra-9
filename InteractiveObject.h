#pragma once
#include "GameObject.h"

class InteractiveObject : public GameObject {
protected:
	std::shared_ptr<PAnimationComponent> m_AC;
	std::shared_ptr<GraphicsComponent> m_GC;
	std::shared_ptr<InteractComponent> m_IC;

public:
	InteractiveObject(std::string name);

	virtual std::shared_ptr<AnimationComponent> getAC() override;
	virtual std::shared_ptr<GraphicsComponent> getGC() override;
	std::shared_ptr<InteractComponent> getIC();
	virtual void update(float dt) override;
	virtual void updateGC(float dt) override;
	virtual void draw(RenderWindow& window);
};