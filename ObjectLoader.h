#pragma once
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include "ObjectHeaders.h"

class ObjectLoader {
private:
	std::vector<std::string> m_LevelsToLoad{ "bar", "main", "lightbulb_room", "bedroom", "library", "password_room", "abandoned_room", "final_room" };
	std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>>> m_MapOfObjects;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::shared_ptr<GameObject> m_Player;
	std::shared_ptr<GameObject> m_AI;
	Vector2f positionInTiles(Vector2f tilePosition);
	Vector2f convert(Vector2f position);

public:
	ObjectLoader(std::shared_ptr<GameObject> player, std::shared_ptr<GameObject> ai, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects);
	void loadObjects(std::string level);
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> getGameObjects();
	std::shared_ptr<GameObject> findObjectInAll(std::string objectName);
};