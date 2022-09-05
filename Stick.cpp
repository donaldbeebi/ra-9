#include "Stick.h"

Stick::Stick(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "stick";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(1.0f, 1.0f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 3, m_TC);
	m_GC->disableDrawOffset();
	m_HasGC = true;
}