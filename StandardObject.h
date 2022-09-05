#pragma once
#include "GameObject.h"

class StandardObject : public GameObject {
protected:
	std::shared_ptr<LAnimationComponent> m_AC;
	std::shared_ptr<GraphicsComponent> m_GC;

public:
	StandardObject(std::string name);

	virtual std::shared_ptr<AnimationComponent> getAC() override;
	virtual std::shared_ptr<GraphicsComponent> getGC() override;
	virtual std::shared_ptr<InteractComponent> getIC() override;
	virtual void update(float dt) override;
	virtual void updateGC(float dt) override;
	virtual void draw(RenderWindow& window) override;
};