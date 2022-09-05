#include "Nightstand.h"

Nightstand::Nightstand(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "nightstand";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(1.0f, 1.0f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 2, m_TC);
	m_HasGC = true;

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::unmovable, m_TC);
	m_HasCC = true;

	/************************
	***Dialogue Component****
	************************/
	m_DC = std::make_shared<DialogueComponent>(m_Name, 1.0f, false);
	m_HasDC = true;
}