#include "TransformComponent.h"

TransformComponent::TransformComponent(Vector2f initialCenterPosition, Vector2f sizeInTiles) {
	m_Size = sizeInTiles * 64.0f;
	m_Position = initialCenterPosition;
	m_ZValue = 0.0f;
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;
	m_UpSpeed = 0.0f;
	m_DownSpeed = 0.0f;
	m_LeftSpeed = 0.0f;
	m_RightSpeed = 0.0f;

	m_YDimension = 1.0f; //in tile size

	//DEBUG COMPONENT
	if (debugging) {
		m_DebugShape.setPosition(Vector2f(initialCenterPosition.x - m_Size.x / 2.0f, initialCenterPosition.y - m_Size.y / 2.0f));
		m_DebugShape.setSize(m_Size);
		m_DebugShape.setOutlineThickness(1.0f);
		m_DebugShape.setOutlineColor(Color::Red);
		m_DebugShape.setFillColor(Color::Transparent);
	}
}

void TransformComponent::move(Vector2f offset) {
	m_Position += offset;
}

void TransformComponent::teleport(Vector2f tilePosition) {
	m_Position = (tilePosition * 64.0f) + Vector2f(32.0f, 32.0f);
}

Vector2f TransformComponent::getPosition() {
	return m_Position;
}

Vector2f TransformComponent::getLayerPosition() {
	return Vector2f(m_Position.x, m_Position.y + m_ZValue);
}

Vector2f TransformComponent::getDrawPosition() {
	return Vector2f(m_Position.x, m_Position.y - m_ZValue);
}

Vector2f TransformComponent::getSize() {
	return m_Size;
}

Vector2f TransformComponent::getVelocity() {
	return m_Velocity;
}

float& TransformComponent::getZValueRef() {
	return m_ZValue;
}

void TransformComponent::setYDimension(float yDimension) {
	m_YDimension = yDimension;
}

float TransformComponent::getYDimension() {
	return m_YDimension;
}

void TransformComponent::update(float dt) {
	//DEBUG COMPONENT
	if (debugging) {
		m_DebugShape.setPosition(Vector2f(m_Position.x - m_Size.x / 2.0f, m_Position.y - m_Size.y / 2.0f));
	}
	//POTENTIAL JIGGLY BUG AHHHHHHHHH
	//m_Position.x = round(m_Position.x);
	//m_Position.y = round(m_Position.y);
}

void TransformComponent::draw(RenderWindow& window) {
	if (debugging) {
		window.draw(m_DebugShape);
	}
}