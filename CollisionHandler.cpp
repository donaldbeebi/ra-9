#include "CollisionHandler.h"

CollisionHandler::CollisionHandler(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects, std::shared_ptr<Tilemap> tilemap) {
	m_GameObjects = gameObjects;
	m_Tilemap = tilemap;
}

void CollisionHandler::updateCollisions() {
	int currentIndex;
	int otherIndex;
	std::shared_ptr<ColliderComponent> currentCC;
	std::shared_ptr<ColliderComponent> otherCC;
	bool hasCollisions;
	int tempCount = 0;

	do {
		hasCollisions = false;
		currentIndex = 0;
		//for (currentIndex = 0; currentIndex != m_GameObjects->size(); currentIndex++) {
		//	if ((*m_GameObjects)[currentIndex]->hasCC() && (*m_GameObjects)[currentIndex]->getCC()->isEnabled()) {
				//currentCC = (*m_GameObjects)[currentIndex]->getCC();
				currentCC = (*m_GameObjects)[0]->getCC();
				for (otherIndex = 0; otherIndex != m_GameObjects->size(); otherIndex++) {
					if (currentIndex != otherIndex && (*m_GameObjects)[otherIndex]->hasCC() && (*m_GameObjects)[otherIndex]->getCC()->isEnabled()) {
						otherCC = (*m_GameObjects)[otherIndex]->getCC();
						//Collision possible, calculating collisions with objects

						float deltaX = currentCC->getPosition().x - otherCC->getPosition().x;
						float deltaY = currentCC->getPosition().y - otherCC->getPosition().y;
						float intersectX = (currentCC->getHalfSize().x + otherCC->getHalfSize().x) - abs(deltaX);
						float intersectY = (currentCC->getHalfSize().y + otherCC->getHalfSize().y) - abs(deltaY);

						//Object Collision Detected
						if (intersectX > 0.1f && intersectY > 0.1f) {							//collision detected! (0.1 for float point inaccuracy)
							hasCollisions = true;

							float mass;
							if (currentCC->getMass() == otherCC->getMass()) mass = 0.5f;
							else if (currentCC->getMass() > otherCC->getMass()) mass = 1.0f;
							else if (currentCC->getMass() < otherCC->getMass()) mass = 0.0f;
							
							if (intersectX < intersectY) {										//if the objects intersect less along the X-axis
								if (deltaX > 0.0f) {											//if this collider is on the right of the other collider
									currentCC->move(Vector2f(intersectX * (1.0f - mass), 0.0f));
									otherCC->move(Vector2f(-intersectX * mass, 0.0f));
								}
								else {															//if this collider is on the left of the other collider
									currentCC->move(Vector2f(-intersectX * (1.0f - mass), 0.0f));
									otherCC->move(Vector2f(intersectX * mass, 0.0f));
								}
							}
							else {																//if the objects intersects less along the Y-axis
								if (deltaY > 0.0f) {											//if this collider is below the other collider
									currentCC->move(Vector2f(0, intersectY * (1.0f - mass)));
									otherCC->move(Vector2f(0.0f, -intersectY * mass));
								}
								else {															//if this collider is above the other collider
									currentCC->move(Vector2f(0, -intersectY * (1.0f - mass)));
									otherCC->move(Vector2f(0.0f, intersectY * mass));
								}
							}
						}
					}
					//No object collision? then check for tile detection
					if (!hasCollisions) {
						//checking horizontal tiles
						Vector2f tilePosition = m_Tilemap->nearestCTileX(currentCC->getPosition());

						float deltaX = currentCC->getPosition().x - tilePosition.x;
						float deltaY = currentCC->getPosition().y - tilePosition.y;
						float intersectX = (currentCC->getHalfSize().x + 32.0f) - abs(deltaX);
						float intersectY = (currentCC->getHalfSize().y + 32.0f) - abs(deltaY);
						if (intersectX > 0.1f && intersectY > 0.1f) {
							hasCollisions = true;
							if (intersectX < intersectY) {										//if the objects intersect less along the X-axis
								if (deltaX > 0.0f) {											//if this collider is on the right of the other collider
									currentCC->move(Vector2f(intersectX, 0.0f));
								}
								else {															//if this collider is on the left of the other collider
									currentCC->move(Vector2f(-intersectX, 0.0f));
								}
							}
							else {																//if the objects intersects less along the Y-axis
								if (deltaY > 0.0f) {											//if this collider is below the other collider
									currentCC->move(Vector2f(0, intersectY));
								}
								else {															//if this collider is above the other collider
									currentCC->move(Vector2f(0, -intersectY));
								}
							}
						}
						//checking vertical tiles
						tilePosition = m_Tilemap->nearestCTileY(currentCC->getPosition());
						deltaX = currentCC->getPosition().x - tilePosition.x;
						deltaY = currentCC->getPosition().y - tilePosition.y;
						intersectX = (currentCC->getHalfSize().x + 32.0f) - abs(deltaX);
						intersectY = (currentCC->getHalfSize().y + 32.0f) - abs(deltaY);
						if (intersectX > 0.1f && intersectY > 0.1f) {
							hasCollisions = true;
							if (intersectX < intersectY) {										//if the objects intersect less along the X-axis
								if (deltaX > 0.0f) {											//if this collider is on the right of the other collider
									currentCC->move(Vector2f(intersectX, 0.0f));
								}
								else {															//if this collider is on the left of the other collider
									currentCC->move(Vector2f(-intersectX, 0.0f));
								}
							}
							else {																//if the objects intersects less along the Y-axis
								if (deltaY > 0.0f) {											//if this collider is below the other collider
									currentCC->move(Vector2f(0.0f, intersectY));
								}
								else {															//if this collider is above the other collider
									currentCC->move(Vector2f(0.0f, -intersectY));
								}
							}
						}
					}
				}
		//	}
		//}
		//if (hasCollisions) std::cout << "collision detected" << std::endl;
		//tempCount++;
	} while (false); //hasCollisions&& tempCount < 100);
}