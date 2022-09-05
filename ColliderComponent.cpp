#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(Mass mass, std::shared_ptr<TransformComponent> TC) {
	m_Enabled = true;
	m_TC = TC;
	m_Mass = mass;
	m_Offset = Vector2f(0.0f, 0.0f);
}

void ColliderComponent::enable() {
	m_Enabled = true;
}

void ColliderComponent::disable() {
	m_Enabled = false;
}

void ColliderComponent::toggle() {
	m_Enabled = !m_Enabled;
}

bool ColliderComponent::isEnabled() {
	return m_Enabled;
}

Vector2f ColliderComponent::getPosition() {
	return m_TC->getPosition();
}

Vector2f ColliderComponent::getHalfSize() {
	return (m_TC->getSize() / 2.0f);
}

Mass ColliderComponent::getMass() {
	return m_Mass;
}

void ColliderComponent::move(Vector2f offset) {
	m_TC->move(offset);
	//m_TC->move(Vector2f(round(offset.x), round(offset.y)));
}

/*
//mass is how much mass the collider gets relative to the other collider, the more mass the less it moves
void ColliderComponent::applyCollision(std::shared_ptr<ColliderComponent> otherCollider) {
	if (m_Enabled) {
		float deltaX = getPosition().x - otherCollider->getPosition().x;
		float deltaY = getPosition().y - otherCollider->getPosition().y;
		float intersectX = (getHalfSize().x + otherCollider->getHalfSize().x) - abs(deltaX);
		float intersectY = (getHalfSize().y + otherCollider->getHalfSize().y) - abs(deltaY);

		if (intersectX > 0.0f && intersectY > 0.0f) {
			float mass;
			if (m_Mass == otherCollider->getMass()) mass = 0.5f;
			else if (m_Mass > otherCollider->getMass()) mass = 1.0f;
			else if (m_Mass < otherCollider->getMass()) mass = 0.0f;

			if (intersectX < intersectY) {										//if the objects intersect less along the X-axis
				if (deltaX > 0.0f) {											//if this collider is on the right of the other collider
					move(Vector2f(intersectX * (1.0f - mass), 0.0f));
					otherCollider->move(Vector2f(-intersectX * mass, 0.0f));
				}
				else {															//if this collider is on the left of the other collider
					move(Vector2f(-intersectX * (1.0f - mass), 0.0f));
					otherCollider->move(Vector2f(intersectX * mass, 0.0f));
				}
			}
			else {																//if the objects intersects less along the Y-axis
				if (deltaY > 0.0f) {											//if this collider is below the other collider
					move(Vector2f(0, intersectY * (1.0f - mass)));
					otherCollider->move(Vector2f(0.0f, -intersectY * mass));
				}
				else {															//if this collider is above the other collider
					move(Vector2f(0, -intersectY * (1.0f - mass)));
					otherCollider->move(Vector2f(0.0f, intersectY * mass));
				}
			}
		}
	}
}
*/

void ColliderComponent::setCollisionCorrection(Vector2f correction) {
	m_Offset = correction;
}

//This function will run two times to check collision in both directions
Vector2f ColliderComponent::getObjectCollisionCorrection(Vector2f velocity, std::shared_ptr<ColliderComponent> otherCollider) {
	if (otherCollider->isEnabled() && this != otherCollider.get()) {
		float deltaX = getPosition().x + velocity.x - otherCollider->getPosition().x;
		float deltaY = getPosition().y + velocity.y - otherCollider->getPosition().y;
		float intersectX = (getHalfSize().x + otherCollider->getHalfSize().x) - abs(deltaX);
		float intersectY = (getHalfSize().y + otherCollider->getHalfSize().y) - abs(deltaY);
		if (intersectX > 0.0f && intersectY > 0.0f) {		//collision detected!
			if (intersectX < intersectY) {
				if (deltaX > 0.0f) {						//to the right of the other collider
					return Vector2f(intersectX, 0.0f);
				}
				else {										//to the left of the other collider
					return Vector2f(-intersectX, 0.0f);
				}
			}
			if (intersectY < intersectX) {
				if (deltaY > 0.0f) {						//below the other collider
					return Vector2f(0.0f, intersectY);
				}
				else {										//above the other collider
					return Vector2f(0.0f, -intersectY);
				}
			}
		}
	}
	return Vector2f(0.0f, 0.0f);
}

float ColliderComponent::getMapCollisionCorrectionX(Vector2f velocity, Tilemap& tilemap) {
	if (m_Enabled) {
		Vector2f CTilePosition = tilemap.nearestCTileX(getPosition());
		
		float deltaX = getPosition().x + velocity.x - CTilePosition.x;
		float deltaY = getPosition().y - CTilePosition.y;
		float intersectX = (getHalfSize().x + 32.0f) - abs(deltaX);
		float intersectY = (getHalfSize().y + 32.0f) - abs(deltaY);
		if (intersectX > 0.0f && intersectY > 0.0f) {
			if (intersectX < intersectY) {					//Resolving along Y-axis
				if (deltaX > 0.0f) return intersectX;		//to the right of the CTile
				else return -intersectX;					//to the left of the CTile
			}
		}
	}
	return 0.0f;
}

float ColliderComponent::getMapCollisionCorrectionY(Vector2f velocity, Tilemap& tilemap) {
	if (m_Enabled) {
		Vector2f CTilePosition = tilemap.nearestCTileY(getPosition());
		float deltaX = getPosition().x - CTilePosition.x;
		float deltaY = getPosition().y + velocity.y - CTilePosition.y;
		float intersectX = (getHalfSize().x + 32.0f) - abs(deltaX);
		float intersectY = (getHalfSize().y + 32.0f) - abs(deltaY);
		if (intersectX > 0.0f && intersectY > 0.0f) {
			if (intersectY < intersectX) {					//Resolving along Y-axis
				if (deltaY > 0.0f) return intersectY;		//below the CTile
				else return -intersectY;					//above the CTile
			}
		}
	}
	return 0.0f;
}
