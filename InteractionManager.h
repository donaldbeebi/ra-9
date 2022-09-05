#pragma once
//IMPLEMENT - event polling system
#include <memory>
#include <queue>
#include "GameObject.h"

class InteractionManager {
private:
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;

public:
	InteractionManager(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
	std::string getAction();
};