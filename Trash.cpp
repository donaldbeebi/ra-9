#include "Trash.h"

Trash::Trash(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "trash";

	/************************
	***Transform Component***
	************************/
	if (m_Name == "bigtrashcan") {
		m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(1.0f, 0.7f));
	}
	else if (m_Name == "trashbag") {
		m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.8f, 0.5f));
	}
	else if (m_Name == "trashbox") {
		m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(1.5f, 0.7f));
	}
	else if (m_Name == "peel") {
		m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.2f, 0.2f));
	}
	m_TC->setYDimension(2.0f);
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
	if (m_Name == "trashbox") {
		m_DC = std::make_shared<DialogueComponent>(m_Name, 1.5f, false); 
	}
	else m_DC = std::make_shared<DialogueComponent>(m_Name, 1.0f, false);
	m_HasDC = true;
}