#pragma once
#include "GraphicsComponent.h"

class StaticGraphicsComponent : public GraphicsComponent {
public:
	StaticGraphicsComponent(std::string texture, unsigned int stateCount, std::shared_ptr<TransformComponent> TC);
	virtual void disableDrawOffset() override;

};