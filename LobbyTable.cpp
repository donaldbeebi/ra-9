#include "LobbyTable.h"

LobbyTable::LobbyTable(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "lobbytable";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(3.5f, 2.7f));
	m_TC->setYDimension(3.0f);
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 5, m_TC);
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