#include "Fallenshelf.h"

FallenShelf::FallenShelf(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "fallenshelf";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(2.5f, 2.5f));
	m_TC->setYDimension(2.5f);
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

	/************************
	***Dialogue Component****
	************************/
	m_DC = std::make_shared<DialogueComponent>(m_Name, 2.5f, false);
	m_HasDC = true;
}