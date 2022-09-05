#include "BarFront.h"

BarFront::BarFront(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "barfront";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(2.0f, 2.0f));
	m_TC->setYDimension(1.0f);
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 1, m_TC);
	m_HasGC = true;
}