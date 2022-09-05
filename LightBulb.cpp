#include "LightBulb.h"

LightBulb::LightBulb(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "lightbulb";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.4f, 0.2f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 2, m_TC);
	m_HasGC = true;
	if (m_Name == "lightbulb1" || m_Name == "lightbulb3" || m_Name == "lightbulb5") {
		m_GC->setState(1);
	}

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::unmovable, m_TC);
	m_HasCC = true;

	/************************
	***Dialogue Component****
	************************/
	m_DC = std::make_shared<DialogueComponent>(m_Tag, 1.0f, false);
	m_HasDC = true;
}