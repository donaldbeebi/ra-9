#include "ObjectLoader.h"

ObjectLoader::ObjectLoader(std::shared_ptr<GameObject> player, std::shared_ptr<GameObject> ai, std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects) {
	m_Player = player;
	m_AI = ai;
	m_GameObjects = gameObjects;
	for (auto it = m_LevelsToLoad.begin(); it != m_LevelsToLoad.end(); it++) {
		m_MapOfObjects[(*it)] = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();
		std::ifstream inputFile("levels/" + (*it) + "_objects.txt");
		std::string line;
		std::stringstream argumentsOfLine;
		std::string argument;

		while (std::getline(inputFile, line)) {
			argumentsOfLine.str(line);
			argumentsOfLine.seekg(std::ios::beg);

			std::getline(argumentsOfLine, argument, ',');
			std::string object = argument;

			std::cout << object << std::endl;

			std::getline(argumentsOfLine, argument, ',');
			std::string name = argument;

			std::getline(argumentsOfLine, argument, ',');
			Vector2f position;
			position.x = stof(argument);
			std::getline(argumentsOfLine, argument, ',');
			position.y = stof(argument);

			if (object == "lever") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Lever>(name, positionInTiles(position)));
			}
			else if (object == "cylinder") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Cylinder>(name, positionInTiles(position)));
			}
			else if (object == "dooru") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<DoorU>(name, positionInTiles(position)));
			}
			else if (object == "doorr") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<DoorR>(name, positionInTiles(position)));
			}
			else if (object == "doorl") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<DoorL>(name, positionInTiles(position)));
			}
			else if (object == "doorb") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<DoorB>(name, positionInTiles(position)));
			}
			else if (object.find("chair") != std::string::npos) {
				auto temp = std::make_shared<Chair>(name, positionInTiles(position));
				switch (object.back()) {
				case 'u':
					temp->getGC()->setState(0);
					break;
				case 'l':
					temp->getGC()->setState(1);
					break;
				case 'r':
					temp->getGC()->setState(2);
					break;
				case 'd':
					temp->getGC()->setState(3);
					break;
				}
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "table") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Table>(name, positionInTiles(position)));
			}
			else if (object.find("torch") != std::string::npos) {
				auto temp = std::make_shared<Torch>(name, positionInTiles(position));
				switch (object.back()) {
				case 'u':
					temp->getGC()->setState(0);
					break;
				case 'l':
					temp->getGC()->setState(1);
					break;
				case 'r':
					temp->getGC()->setState(2);
					break;
				}
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "bookshelf") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Bookshelf>(name, positionInTiles(position)));
			}
			else if (object.find("lamp") != std::string::npos) {
				auto temp = std::make_shared<Lamp>(name, positionInTiles(position));
				switch (object.back()) {
				case 'u':
					temp->getGC()->setState(0);
					break;
				case 'l':
					temp->getGC()->setState(1);
					break;
				case 'r':
					temp->getGC()->setState(2);
					break;
				}
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "bartable") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<BarTable>(name, positionInTiles(position)));
			}
			else if (object == "beverageshelf") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<BeverageShelf>(name, positionInTiles(position)));
			}
			else if (object == "barstool") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<BarStool>(name, positionInTiles(position)));
			}
			else if (object.find("diningtable") != std::string::npos) {
				auto temp = std::make_shared<DiningTable>(name, positionInTiles(position));
				temp->getGC()->setState(object.back() - '1');
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "lightbulb") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<LightBulb>(name, positionInTiles(position)));
			}
			else if (object == "ai") {
				m_MapOfObjects[(*it)]->push_back(m_AI);
				m_AI->getTC()->teleport(position);
			}
			else if (object == "numberbutton") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<NumberButton>(name, positionInTiles(position)));
			}
			else if (object == "bigbutton") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<BigButton>(name, positionInTiles(position)));
			}
			else if (object == "desk") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Desk>(name, positionInTiles(position)));
			}
			else if (object == "trashcan") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<TrashCan>(name, positionInTiles(position)));
			}
			else if (object == "closet") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Closet>(name, positionInTiles(position)));
			}
			else if (object.find("nightstand") != std::string::npos) {
				auto temp = std::make_shared<Nightstand>(name, positionInTiles(position));
				switch (object.back()) {
				case '1':
					temp->getGC()->setState(0);
					break;
				case '2':
					temp->getGC()->setState(1);
					break;
				}
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "bed") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Bed>(name, positionInTiles(position)));
			}
			else if (object == "guitar") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Guitar>(name, positionInTiles(position)));
			}
			else if (object == "television") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Television>(name, positionInTiles(position)));
			}
			else if (object == "vase") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Vase>(name, positionInTiles(position)));
			}
			else if (object == "receptiondesk") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<ReceptionDesk>(name, positionInTiles(position)));
			}
			else if (object.find("receptionobject") != std::string::npos) {
				auto temp = std::make_shared<ReceptionObject>(name, positionInTiles(position));
				temp->getGC()->setState(object.back() - '1');
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object.find("cushion") != std::string::npos) {
				auto temp = std::make_shared<Cushion>(name, positionInTiles(position));
				temp->getGC()->setState(object.back() - '1');
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object.find("lobbytable") != std::string::npos) {
				auto temp = std::make_shared<LobbyTable>(name, positionInTiles(position));
				temp->getGC()->setState(object.back() - '1');
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "key") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Key>(name, positionInTiles(position)));
			}
			else if (object.find("singlebook") != std::string::npos) {
				auto temp = std::make_shared<SingleBook>(name, positionInTiles(position));
				temp->getGC()->setState(object.back() - '1');
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object.find("bookpile") != std::string::npos) {
				auto temp = std::make_shared<BookPile>(name, positionInTiles(position));
				temp->getGC()->setState(object.back() - '1');
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "fallenshelf") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<FallenShelf>(name, positionInTiles(position)));
			}
			else if (object.find("trash") != std::string::npos) {
				auto temp = std::make_shared<Trash>(name, positionInTiles(position));
				temp->getGC()->setState(object.back() - '1');
				m_MapOfObjects[(*it)]->push_back(move(temp));
			}
			else if (object == "jukebox") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<JukeBox>(name, positionInTiles(position)));
			}
			else if (object == "printer") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<Printer>(name, positionInTiles(position)));
			}
			else if (object == "barfront") {
				m_MapOfObjects[(*it)]->push_back(std::make_shared<BarFront>(name, positionInTiles(position)));
			}
		}
		inputFile.close();
	}
	m_GameObjects->push_back(m_Player);
	m_GameObjects->insert(m_GameObjects->end(), m_MapOfObjects["bar"]->begin(), m_MapOfObjects["bar"]->end());
}

void ObjectLoader::loadObjects(std::string level) {
	m_GameObjects->resize(1);
	m_GameObjects->insert(m_GameObjects->end(), m_MapOfObjects[level]->begin(), m_MapOfObjects[level]->end());
}

std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> ObjectLoader::getGameObjects() {
	return m_GameObjects;
}

std::shared_ptr<GameObject> ObjectLoader::findObjectInAll(std::string objectName) {
	for (auto it1 = m_MapOfObjects.begin(); it1 != m_MapOfObjects.end(); it1++) {
		for (auto it2 = (*it1).second->begin(); it2 != (*it1).second->end(); it2++) {
			if ((*it2)->getName() == objectName) {
				return (*it2);
			}
		}
	}
	return nullptr;
}

Vector2f ObjectLoader::positionInTiles(Vector2f tilePosition) {
	Vector2f actualPosition;
	actualPosition.x = tilePosition.x * 64.0f + (64.0f / 2.0f);
	actualPosition.y = tilePosition.y * 64.0f + (64.0f / 2.0f);
	return actualPosition;
}

Vector2f ObjectLoader::convert(Vector2f position) {
	return position;
}
