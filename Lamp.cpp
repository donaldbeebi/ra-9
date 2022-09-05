#include "Lamp.h"

Lamp::Lamp(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "lamp";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.7f, 0.7f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 3, m_TC);
	m_HasGC = true;
}