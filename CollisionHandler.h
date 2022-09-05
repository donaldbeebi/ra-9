#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Tilemap.h"

class CollisionHandler {
private:
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::shared_ptr<Tilemap> m_Tilemap;

public:
	CollisionHandler(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects, std::shared_ptr<Tilemap> tilemap);
	void updateCollisions();
};