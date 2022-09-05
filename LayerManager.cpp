#include "LayerManager.h"

LayerManager::LayerManager(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects) {
	m_GameObjects = gameObjects;
	m_DrawableObjects = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();
	
	auto it = gameObjects->begin();
	for (it; it != gameObjects->end(); it++) {
		if ((*it)->hasGC()) {
			m_DrawableObjects->push_back(*it);
		}
	}
}

void LayerManager::updateDrawableObjects() {
	m_DrawableObjects->clear();

	auto it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		if ((*it)->hasGC()) {
			m_DrawableObjects->push_back(*it);
		}
	}
}

void LayerManager::updateLayer() {
	std::sort(m_DrawableObjects->begin(), m_DrawableObjects->end(), [](const std::shared_ptr<GameObject>& first , const std::shared_ptr<GameObject>& last)
		{ return first->getTC()->getLayerPosition().y < last->getTC()->getLayerPosition().y; });
}

void LayerManager::draw(RenderWindow& window) {
	auto it = m_DrawableObjects->begin();
	for (it; it != m_DrawableObjects->end(); it++) {
		(*it)->draw(window);
	}
}