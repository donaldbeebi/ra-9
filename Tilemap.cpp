#include "Tilemap.h"

Vector2i Tilemap::convert(int id) {
	Vector2i size = Vector2i(m_TileSheet.getSize().x / 64.0f, m_TileSheet.getSize().y / 64.0f);
	Vector2i position;
	position.x = id % size.x;
	position.y = id / size.x;
	position *= 64;
	return Vector2i(position);
}

Tilemap::Tilemap() {
	m_CL = "bar";
	m_PL = "none";

	/*************************
	******Parsing tilemap*****
	*************************/
	m_TileSheet = TextureManager::getTexture("graphics/backgrounds/tile_sheet.png");

	/*************************
	****Loading from files****
	*************************/
	std::ifstream inputFile("levels/" + m_CL + ".txt");
	std::string line;
	std::stringstream row(line);
	std::string id;

	//Calculating the world size
	while (std::getline(inputFile, line)) {
		m_WorldSize.y++;
	}

	row.str(line);

	while (std::getline(row, id, ',')) {
		m_WorldSize.x++;
	}

	std::cout << "Worldsize: " << m_WorldSize.x << " " << m_WorldSize.y << std::endl;

	//Going back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, std::ios::beg);

	//Preparing the 2D array to hold the int values from the file
	int** levelArray = new int* [m_WorldSize.x];	//allocating a number equal to the y world size of char pointers
	for (int i = 0; i < m_WorldSize.x; i++) {
		levelArray[i] = new int[m_WorldSize.y];		//allocating each pointer a number equal to the x world size of chars (not pointers this time)
	}

	for (int y = 0; y < m_WorldSize.y; y++) {
		std::getline(inputFile, line);
		row.clear();
		row.str(line);
		for (int x = 0; x < m_WorldSize.x; x++) {
			std::getline(row, id, ',');
			levelArray[x][y] = stoi(id);
		}
	}

	//Closing the file
	inputFile.close();

	/*************************
	****Setting up the VA*****
	*************************/
	m_VA.setPrimitiveType(Quads);
	m_VA.resize(m_WorldSize.x * m_WorldSize.y * 4);

	//Positioning each vertex
	int currentVertex = 0;

	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			currentVertex++;
		}
	}

	//Setting up the tiles
	currentVertex = 0;

	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			Vector2i type = convert(levelArray[x][y]);
			m_VA[currentVertex].texCoords = Vector2f(type.x, type.y);
			currentVertex++;
			m_VA[currentVertex].texCoords = Vector2f(type.x + TILE_SIZE, type.y);
			currentVertex++;
			m_VA[currentVertex].texCoords = Vector2f(type.x + TILE_SIZE, type.y + TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].texCoords = Vector2f(type.x, type.y + TILE_SIZE);
			currentVertex++;
		}
	}

//#ifdef debuggingOnConsole
	//std::cout << "levelArray values:" << std::endl;
	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			//std::cout << levelArray[x][y] << " ";
		}
		//std::cout << std::endl;
	}
//#endif

	/*************************
	***Parsing collision map**
	*************************/

	/*************************
	****Loading from files****
	*************************/
	inputFile.open("levels/" + m_CL + "_collision.txt");

	m_CollisionMap = new bool* [m_WorldSize.x];
	for (int i = 0; i < m_WorldSize.x; i++) {
		m_CollisionMap[i] = new bool[m_WorldSize.y];
	}

	for (int y = 0; y < m_WorldSize.y; y++) {
		std::getline(inputFile, line);
		row.clear();
		row.str(line);
		for (int x = 0; x < m_WorldSize.x; x++) {
			std::getline(row, id, ',');
			m_CollisionMap[x][y] = (id != "-1");
		}
	}

	inputFile.close();

//#ifdef debuggingOnConsole
	//std::cout << "m_CollisionMap values:" << std::endl;
	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			//std::cout << m_CollisionMap[x][y] << " ";
		}
		//std::cout << std::endl;
	}
//#endif
}

bool** Tilemap::getCollisionMap() {
	return m_CollisionMap;
}

Vector2i Tilemap::getWorldSize() {
	return m_WorldSize;
}

Vector2f Tilemap::nearestCTileX(Vector2f centerPosition) {
	Vector2i tilePosition = Vector2i(centerPosition / 64.0f);
	tilePosition.x = std::min(m_WorldSize.x - 1, std::max(0, tilePosition.x));
	tilePosition.y = std::min(m_WorldSize.y - 1, std::max(0, tilePosition.y));

	int position1;
	int position2;
	int distance1;
	int distance2;

	for (position1 = tilePosition.x; position1 < m_WorldSize.x; position1++) {
		if (m_CollisionMap[position1][tilePosition.y] == true) break;
	}
	distance1 = float(position1) * 64.0f + 32.0f - centerPosition.x;

	for (position2 = tilePosition.x; position2 >= 0; position2--) {
		if (m_CollisionMap[position2][tilePosition.y] == true) break;
	}
	distance2 = centerPosition.x - float(position2) * 64.0f + 32.0f;

	if (distance1 < distance2) return Vector2f(float(position1) * 64.0f + 32.0f, float(tilePosition.y) * 64.0f + 32.0f);
	if (distance1 < distance2) return Vector2f(float(position1) * 64.0f + 32.0f, float(tilePosition.y) * 64.0f + 32.0f);
	else return Vector2f(float(position2) * 64.0f + 32.0f, float(tilePosition.y) * 64.0f + 32.0f);
}

Vector2f Tilemap::nearestCTileY(Vector2f centerPosition) {
	Vector2i tilePosition = Vector2i(centerPosition / 64.0f);
	tilePosition.x = std::min(m_WorldSize.x - 1, std::max(0, tilePosition.x));
	tilePosition.y = std::min(m_WorldSize.y - 1, std::max(0, tilePosition.y));

	int position1;
	int position2;
	int distance1;
	int distance2;
	for (position1 = tilePosition.y; position1 < m_WorldSize.y; position1++) {
		if (m_CollisionMap[tilePosition.x][position1] == true) break;
	}
	distance1 = float(position1) * 64.0f + 32.0f - centerPosition.y;

	for (position2 = tilePosition.y; position2 >= 0; position2--) {
		if (m_CollisionMap[tilePosition.x][position2] == true) break;
	}
	distance2 = centerPosition.y - float(position2) * 64.0f + 32.0f;
	if (distance1 < distance2) return Vector2f(float(tilePosition.x) * 64.0f + 32.0f, float(position1) * 64.0f + 32.0f);
	else return Vector2f(float(tilePosition.x) * 64.0f + 32.0f, float(position2) * 64.0f + 32.0f);
}

Vector2f Tilemap::getSpawnLocation() {
	if (m_PL == "main") {
		if (m_CL == "bar") {
			return Vector2f(9.5f, 15.0f);
		}
		else if (m_CL == "lightbulb_room") {
			return Vector2f(23.0f, 8.5f);
		}
		else if (m_CL == "bedroom") {
			return Vector2f(5.5f, 13.0f);
		}
		else if (m_CL == "library") {
			return Vector2f(7.5f, 14.0f);
		}
		else if (m_CL == "password_room") {
			return Vector2f(3.0f, 10.5f);
		}
	}
	else if (m_PL == "bar") {
		if (m_CL == "main") {
			return Vector2f(8.5f, 6.0f);
		}
	}
	else if (m_PL == "bedroom") {
		if (m_CL == "main") {
			return Vector2f(28.5f, 8.0f);
		}
	}
	else if (m_PL == "library") {
		if (m_CL == "main") {
			return Vector2f(21.5f, 8.0f);
		}
	}
	else if (m_PL == "password_room") {
		if (m_CL == "main") {
			return Vector2f(33.0f, 14.5f);
		}
		else if (m_CL == "final_room") {
			return Vector2f(8.5f, 10.0f);
		}
	}
	else if (m_PL == "abandoned_room") {
		if (m_CL == "lightbulb_room") {
			return Vector2f(2.0f, 12.0f);
		}
	}
	else if (m_PL == "lightbulb_room") {
		if (m_CL == "abandoned_room") {
			return Vector2f(16.0f, 16.0f);
		}
		if (m_CL == "main") {
			return Vector2f(2.0f, 14.5f);
		}
	}
	else if (m_PL == "final_room") {
		if (m_CL == "password_room") {
			return Vector2f(9.5f, 12.0f);
		}
	}
	return Vector2f(10.0f, 10.0f);
}

std::string Tilemap::getCurrentLocation() {
	return m_CL;
}

void Tilemap::loadLevel(std::string level) {
	m_PL = m_CL;
	m_CL = level;

	//initializing variables
	m_WorldSize.x = 0;
	m_WorldSize.y = 0;

	/*************************
	****Loading from files****
	*************************/
	std::ifstream inputFile("levels/" + level + ".txt");
	std::string line;
	std::stringstream row(line);
	std::string id;

	//Calculating the world size
	while (std::getline(inputFile, line)) {
		m_WorldSize.y++;
	}

	row.str(line);

	while (std::getline(row, id, ',')) {
		m_WorldSize.x++;
	}

	//Going back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, std::ios::beg);

	//Preparing the 2D array to hold the int values from the file
	int** levelArray = new int* [m_WorldSize.x];	//allocating a number equal to the y world size of char pointers
	for (int i = 0; i < m_WorldSize.x; i++) {
		levelArray[i] = new int[m_WorldSize.y];		//allocating each pointer a number equal to the x world size of chars (not pointers this time)
	}

	for (int y = 0; y < m_WorldSize.y; y++) {
		std::getline(inputFile, line);
		row.clear();
		row.str(line);
		for (int x = 0; x < m_WorldSize.x; x++) {
			std::getline(row, id, ',');
			levelArray[x][y] = stoi(id);
		}
	}

	//Closing the file
	inputFile.close();

	/*************************
	****Setting up the VA*****
	*************************/
	m_VA.setPrimitiveType(Quads);
	m_VA.resize(m_WorldSize.x * m_WorldSize.y * 4);

	//Positioning each vertex
	int currentVertex = 0;

	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
			currentVertex++;
		}
	}

	//Setting up the tiles
	currentVertex = 0;

	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			Vector2i type = convert(levelArray[x][y]);
			m_VA[currentVertex].texCoords = Vector2f(type.x, type.y);
			currentVertex++;
			m_VA[currentVertex].texCoords = Vector2f(type.x + TILE_SIZE, type.y);
			currentVertex++;
			m_VA[currentVertex].texCoords = Vector2f(type.x + TILE_SIZE, type.y + TILE_SIZE);
			currentVertex++;
			m_VA[currentVertex].texCoords = Vector2f(type.x, type.y + TILE_SIZE);
			currentVertex++;
		}
	}

	//#ifdef debuggingOnConsole
	//std::cout << "levelArray values:" << std::endl;
	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			//std::cout << levelArray[x][y] << " ";
		}
		//std::cout << std::endl;
	}
	//#endif

		/*************************
		***Parsing collision map**
		*************************/

		/*************************
		****Loading from files****
		*************************/
	inputFile.open("levels/" + level + "_collision.txt");

	delete[] m_CollisionMap;

	m_CollisionMap = new bool* [m_WorldSize.x];
	for (int i = 0; i < m_WorldSize.x; i++) {
		m_CollisionMap[i] = new bool[m_WorldSize.y];
	}

	for (int y = 0; y < m_WorldSize.y; y++) {
		std::getline(inputFile, line);
		row.clear();
		row.str(line);
		for (int x = 0; x < m_WorldSize.x; x++) {
			std::getline(row, id, ',');
			m_CollisionMap[x][y] = (id != "-1");
		}
	}

	inputFile.close();

	//#ifdef debuggingOnConsole
	//std::cout << "m_CollisionMap values:" << std::endl;
	for (int y = 0; y < m_WorldSize.y; y++) {
		for (int x = 0; x < m_WorldSize.x; x++) {
			//std::cout << m_CollisionMap[x][y] << " ";
		}
		//std::cout << std::endl;
	}
	//#endif
}

void Tilemap::draw(RenderWindow& window) {
	window.draw(m_VA, &m_TileSheet);
}