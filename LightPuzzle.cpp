#include "LightPuzzle.h"

LightPuzzle::LightPuzzle(std::string name, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects) 
	: Puzzle(name, gameObjects) {}

void LightPuzzle::enable() {
	m_IsEnabled = true;
	auto it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		if ((*it)->getName() == "lightbulb1") {
			m_TriggerObjects->push_back(*it);
		}
		if ((*it)->getName() == "lightbulb2") {
			m_TriggerObjects->push_back(*it);
		}
		if ((*it)->getName() == "lightbulb3") {
			m_TriggerObjects->push_back(*it);
		}
		if ((*it)->getName() == "lightbulb4") {
			m_TriggerObjects->push_back(*it);
		}
		if ((*it)->getName() == "lightbulb5") {
			m_TriggerObjects->push_back(*it);
		}
	}
}

void LightPuzzle::update() {
	if (m_IsEnabled && !m_IsComplete) {
		auto it = m_TriggerObjects->begin();
		m_IsComplete = true;
		for (it; it != m_TriggerObjects->end(); it++) {
			if ((*it)->getGC()->getState() == 0) {
				m_IsComplete = false;
				break;
			}
		}
	}
}