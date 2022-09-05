#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;

class TransformComponent {
private:
	Vector2f m_Position;
	Vector2f m_Velocity;
	Vector2f m_Size;

	float m_UpSpeed;
	float m_DownSpeed;
	float m_LeftSpeed;
	float m_RightSpeed;
	
	float m_ZValue;

	float m_YDimension;

	//DEBUG COMPONENT
	RectangleShape m_DebugShape;
	bool debugging = true;

public:
	TransformComponent(Vector2f initialCenterPosition, Vector2f sizeInTiles);

	void move(Vector2f offset);
	void teleport(Vector2f tilePosition);

	Vector2f getPosition();
	Vector2f getLayerPosition();
	Vector2f getDrawPosition();
	Vector2f getVelocity();
	Vector2f getSize();
	float& getZValueRef();

	void setYDimension(float yDimension); //necessary for proper setting of the draw offset
	float getYDimension();

	void update(float dt);

	//DEBUG COMPONENT
	virtual void draw(RenderWindow& window);
};