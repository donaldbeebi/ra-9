#include "BeverageShelf.h"

BeverageShelf::BeverageShelf(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "beverageshelf";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(5.6f, 1.0f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 1, m_TC);
	m_HasGC = true;

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::unmovable, m_TC);
	m_HasCC = true;
}