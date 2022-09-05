#include "InteractiveObject.h"

InteractiveObject::InteractiveObject(std::string name) : GameObject(name) {
	m_AC = nullptr;
	m_GC = nullptr;
	m_IC = nullptr;
}

std::shared_ptr<AnimationComponent> InteractiveObject::getAC() {
	return  m_AC;
}

std::shared_ptr<GraphicsComponent> InteractiveObject::getGC() {
	return m_GC;
}

std::shared_ptr<InteractComponent> InteractiveObject::getIC() {
	return m_IC;
}

void InteractiveObject::update(float dt) {
	if (m_HasTC) {
		m_TC->update(dt);
	}
	if (m_HasIC) {
		m_IC->update();
	}
}

void InteractiveObject::updateGC(float dt) {
	if (m_HasGC) {
		m_GC->update(dt);
	}
}

void InteractiveObject::draw(RenderWindow& window) {
	if(m_HasGC) {
		m_GC->draw(window);
	}
}