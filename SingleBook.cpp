#include "SingleBook.h"

SingleBook::SingleBook(std::string name, Vector2f initialCenterPosition) : StandardObject(name) {
	m_Tag = "singlebook";

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(1.0f, 1.0f));
	m_TC->getZValueRef() = -64.0f;
	m_HasTC = true;

	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<StaticGraphicsComponent>(m_Tag, 7, m_TC);
	m_HasGC = true;
}