#include "DDoor.h"

DDoorF::DDoorF(std::string name, Vector2f initialCenterPosition) : InteractiveObject(name) {
	m_Tag = "ddoor";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.8f, 0.4f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>("ddoor", 2, m_TC);
	m_HasGC = true;

	/************************
	***Interact Component****
	************************/
	m_IC = std::make_shared<InteractComponent>(m_Name, 1.0f, m_GC);
	m_HasIC = true;
}