#include "Torch.h"

Torch::Torch(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "torch";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.7f, 0.7f));
	m_HasTC = true;

	/************************
	***Animation Component***
	************************/
	m_AC = std::make_shared<LAnimationComponent>(m_Tag, Vector2u(4, 3));
	m_AC->setConstantSwitchTime(0.15f);
	m_AC->play();
	m_HasAC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<AnimatedGraphicsComponent>(m_AC, m_TC);
	m_HasGC = true;
}