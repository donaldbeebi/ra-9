#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include "TextureManager.h"

using namespace sf;

class Tilemap {
private:
	VertexArray m_VA;
	Texture m_TileSheet;
	const int TILE_SIZE = 64;
	const int TILE_TYPES = 3;
	Vector2i m_WorldSize;
	bool** m_CollisionMap;
	std::string m_CL;
	std::string m_PL;

	Vector2i convert(int id);

public:
	Tilemap();

	bool** getCollisionMap();
	Vector2i getWorldSize();
	Vector2f nearestCTileX(Vector2f centerPosition);
	Vector2f nearestCTileY(Vector2f centerPosition);

	Vector2f getSpawnLocation();
	std::string getCurrentLocation();

	void loadLevel(std::string level);
	
	void draw(RenderWindow& window);
};