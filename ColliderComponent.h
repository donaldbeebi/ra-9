//Dependent on TC
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "TransformComponent.h"
#include "Tilemap.h"

using namespace sf;

enum class Mass { movable = 1, unmovable = 2 };

class ColliderComponent {
private:
	bool m_Enabled;
	std::shared_ptr<TransformComponent> m_TC;
	Mass m_Mass;
	Vector2f m_Offset;

public:
	ColliderComponent(Mass mass, std::shared_ptr<TransformComponent> TC);

	void enable();
	void disable();
	void toggle();
	bool isEnabled();

	Vector2f getPosition();
	Vector2f getHalfSize();
	Mass getMass();

	void move(Vector2f offset);
	//void applyCollision(std::shared_ptr<ColliderComponent> otherCollider);
	void setCollisionCorrection(Vector2f correction);
	Vector2f getObjectCollisionCorrection(Vector2f velocity, std::shared_ptr<ColliderComponent> otherCollider);
	float getMapCollisionCorrectionX(Vector2f velocity, Tilemap& tilemap);
	float getMapCollisionCorrectionY(Vector2f velocity, Tilemap& tilemap);
};