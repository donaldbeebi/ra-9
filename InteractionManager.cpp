#include "InteractionManager.h"

InteractionManager::InteractionManager(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects) {
	m_GameObjects = gameObjects;
}

std::string InteractionManager::getAction() {
	for (auto it = m_GameObjects->begin(); it != m_GameObjects->end(); it++) {
		if ((*it)->hasIC()) {
			std::string tempAction = (*it)->getIC()->getAction();
			if (tempAction != "none") {
				//std::cout << "action found" << std::endl;
				return tempAction;
			}
		}
	}
	return "none";
}