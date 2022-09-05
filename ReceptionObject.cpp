#include "ReceptionObject.h"

ReceptionObject::ReceptionObject(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "receptionobject";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(1.0f, 1.0f));
	if (m_Name == "receptiontelephone" || m_Name == "receptioncomputer") {
		m_TC->getZValueRef() = 64.0f;
	}
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 3, m_TC);
	m_HasGC = true;

	/************************
	***Dialogue Component****
	************************/
	m_DC = std::make_shared<DialogueComponent>(m_Name, 1.0f, false);
	m_HasDC = true;
}