#include "Cushion.h"

Cushion::Cushion(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "cushion";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.8f, 0.5f));
	m_TC->setYDimension(2.0f);
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 3, m_TC);
	m_HasGC = true;

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::unmovable, m_TC);
	m_HasCC = true;
}