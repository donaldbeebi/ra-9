#include "NumberButton.h"

NumberButton::NumberButton(std::string name, Vector2f initialCenterPosition) : InteractiveObject(name) {
	m_Tag = "numberbutton";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.6f, 0.6f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Name, 2, m_TC);
	m_HasGC = true;

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::unmovable, m_TC);
	m_HasCC = true;

	/************************
	***Interact Component****
	************************/
	m_IC = std::make_shared<InteractComponent>(m_Name, 0.6f, m_GC);
	m_HasIC = true;

}