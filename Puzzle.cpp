#include "Puzzle.h"

Puzzle::Puzzle(std::string name, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects){
	m_Name = name;
	m_GameObjects = gameObjects;
	m_TriggerObjects = std::make_unique<std::vector<std::shared_ptr<GameObject>>>();
	m_IsEnabled = false;
	m_IsComplete = false;
}

void Puzzle::disable() {
	m_TriggerObjects->clear();
	m_IsEnabled = false;
}

std::string Puzzle::getName() {
	return m_Name;
}

bool Puzzle::isComplete() {
	return m_IsComplete;
}