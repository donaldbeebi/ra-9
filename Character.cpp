#include "Character.h"

Vector2f Character::dtov(Direction direction) {
	switch (direction) {
	case Direction::up:
		return Vector2f(0.0f, -m_Speed);
		break;
	case Direction::down:
		return Vector2f(0.0f, m_Speed);
		break;
	case Direction::left:
		return Vector2f(-m_Speed, 0.0f);
		break;
	case Direction::right:
		return Vector2f(m_Speed, 0.0f);
		break;
	default:
		return Vector2f(0.0f, 0.0f);
		break;
	}
}

Character::Character(std::string name) : GameObject(name) {
	m_AC = nullptr;
	m_GC = nullptr;

	m_Speed = 0.0f;
	m_IsMoving = false;
	m_CurrentDirection = Direction::down;
	m_CurrentVelocity = Vector2f(0.0f, 0.0f);
}

void Character::move(Direction direction) {
	m_CurrentDirection = direction;
	m_CurrentVelocity += dtov(direction);
	m_IsMoving = true;
}

std::shared_ptr<AnimationComponent> Character::getAC() {
	return m_AC;
}

std::shared_ptr<GraphicsComponent> Character::getGC() {
	return m_GC;
}

std::shared_ptr<InteractComponent> Character::getIC() {
	return nullptr;
}

void Character::update(float dt) {
	m_DT = dt;
	if (m_IsMoving) {
		switch (m_CurrentDirection) {
		case Direction::down:
			m_GC->setState(0);
			break;
		case Direction::right:
			m_GC->setState(1);
			break;
		case Direction::left:
			m_GC->setState(2);
			break;
		case Direction::up:
			m_GC->setState(3);
			break;
		}
		//Moving the character
		if (m_CurrentVelocity.x != 0.0f && m_CurrentVelocity.y != 0.0f) {
			m_CurrentVelocity /= 1.414f;
		}
		m_TC->move(m_CurrentVelocity * dt);
		m_IsMoving = false;
		m_CurrentVelocity = Vector2f(0.0f, 0.0f);
	}
	else {
		switch (m_CurrentDirection) {
		case Direction::down:
			m_GC->setState(4);
			break;
		case Direction::right:
			m_GC->setState(5);
			break;
		case Direction::left:
			m_GC->setState(6);
			break;
		case Direction::up:
			m_GC->setState(7);
			break;
		}
	}
	m_TC->update(dt);
}

void Character::updateGC(float dt) {
	if (m_HasGC) {
		m_GC->update(dt);
	}
}

void Character::draw(RenderWindow& window) {
	if (m_HasGC) {
		m_GC->draw(window);
	}
}