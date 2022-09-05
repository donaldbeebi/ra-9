#include "Lever.h"

Lever::Lever(std::string name, Vector2f initialCenterPosition) : InteractiveObject(name) {
	m_Tag = "lever";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.8f, 0.4f));
	m_HasTC = true;

	/************************
	***Animation Component***
	************************/
	m_AC = std::make_shared<PAnimationComponent>(m_Tag, Vector2u(5, 1));
	m_AC->setConstantSwitchTime(0.05f);
	m_HasAC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<AnimatedGraphicsComponent>(m_AC, m_TC);
	m_HasGC = true;

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::unmovable, m_TC);
	m_HasCC = true;

	/************************
	***Interact Component****
	************************/
	m_IC = std::make_shared<InteractComponent>(m_Name, 1.0f, m_AC);
	m_HasIC = true;
}