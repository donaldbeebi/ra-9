#include "DialogueManager.h"

DialogueManager::DialogueManager(std::shared_ptr<GameObject> ai, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects) {
	m_AI = ai;
	m_GameObjects = gameObjects;
}

DialogueLine DialogueManager::getDialogueLine() {
	DialogueLine temp = m_AI->getDC()->getDialogueLine();
	if (temp.line != "none") return temp;
	auto it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		if ((*it)->hasDC()) {
			temp = (*it)->getDC()->getDialogueLine();
			if (temp.line != "none") {
				if (!(*it)->getDC()->printWithTitle()) temp.speaker = "none";
				m_CurrentDC = (*it)->getDC();
				return temp;
			}
		}
	}
	return DialogueLine("none", "none");
}

std::shared_ptr<DialogueComponent> DialogueManager::getCurrentDC() {
	return m_CurrentDC;
}