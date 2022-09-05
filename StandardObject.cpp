#include "StandardObject.h"

StandardObject::StandardObject(std::string name) : GameObject(name) {
	m_AC = nullptr;
	m_GC = nullptr;
}

std::shared_ptr<AnimationComponent> StandardObject::getAC() {
	return  m_AC;
}

std::shared_ptr<GraphicsComponent> StandardObject::getGC() {
	return m_GC;
}

std::shared_ptr<InteractComponent> StandardObject::getIC() {
	return  nullptr;
}

void StandardObject::update(float dt) {
	if (m_HasTC) {
		m_TC->update(dt);
	}
}

void StandardObject::updateGC(float dt) {
	if (m_HasGC) {
		m_GC->update(dt);
	}
}

void StandardObject::draw(RenderWindow& window) {
	if (m_HasGC) {
		m_GC->draw(window);
	}
}