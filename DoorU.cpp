#include "DoorU.h"

DoorU::DoorU(std::string name, Vector2f initialCenterPosition) : InteractiveObject(name) {
	m_Tag = "dooru";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.8f, 0.4f));
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 1, m_TC);
	m_HasGC = true;

	/************************
	***Interact Component****
	************************/
	m_IC = std::make_shared<InteractComponent>(m_Name, 1.0f, m_GC);
	m_HasIC = true;

	if (m_Name == "door_main_library" || m_Name == "door_main_bedroom" || m_Name == "door_final_room_password_room") {
		/************************
		***Dialogue Component****
		************************/
		m_DC = std::make_shared<DialogueComponent>(m_Name, 1.0f, false);
		m_HasDC = true;
	}
}