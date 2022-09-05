#include "Player.h"

Player::Player(std::string name, Vector2f initialCenterPosition) : Character(name) {
	m_Tag = "player";
	m_Speed = 600.0f;

	/************************
	***Transform Component***
	************************/
	m_TC = std::make_shared<TransformComponent>(initialCenterPosition, Vector2f(0.6f, 0.4f));
	m_TC->setYDimension(2.0f);
	m_HasTC = true;

	/************************
	***Animation Component***
	************************/
	m_AC = std::make_shared<LAnimationComponent>(m_Tag, Vector2u(6, 8));
	m_AC->setConstantSwitchTime(0.1f);
	m_AC->play();
	m_HasAC = true;
	
	/************************
	***Graphics Component****
	************************/
	m_GC = std::make_shared<CharacterGraphicsComponent>(m_AC, m_TC);
	m_CurrentDirection = Direction::up;
	m_GC->setState(3);
	m_HasGC = true;

	/************************
	***Collider Component****
	************************/
	m_CC = std::make_shared<ColliderComponent>(Mass::movable, m_TC);
	m_HasCC = true;
}