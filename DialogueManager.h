#pragma once
#include "GameObject.h"
#include <memory>
#include <vector>

class DialogueManager {
private:
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::shared_ptr<GameObject> m_AI;
	std::shared_ptr<DialogueComponent> m_CurrentDC;

public:
	DialogueManager(std::shared_ptr<GameObject> ai, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);

	DialogueLine getDialogueLine();
	std::shared_ptr<DialogueComponent> getCurrentDC();
};