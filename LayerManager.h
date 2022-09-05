#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>
#include "GameObject.h"

using namespace std;

class LayerManager {
private:
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_DrawableObjects;

public:
	LayerManager(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
	void updateDrawableObjects();
	void updateLayer();
	void draw(RenderWindow& window);
};