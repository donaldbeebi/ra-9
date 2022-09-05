#include "CharacterGraphicsComponent.h"

CharacterGraphicsComponent::CharacterGraphicsComponent(std::shared_ptr<AnimationComponent> animation , std::shared_ptr<TransformComponent> TC) 
	: AnimatedGraphicsComponent (animation, TC){
	m_CurrentDirection = Direction::down;
}

void CharacterGraphicsComponent::faceLeft() {
	if (m_CurrentDirection != Direction::left) m_Sprite.setScale(-1.0, 1.0f);
	m_CurrentDirection = Direction::left;
}

void CharacterGraphicsComponent::faceRight() {
	if (m_CurrentDirection != Direction::right) m_Sprite.setScale(1.0f, 1.0f);
	m_CurrentDirection = Direction::right;
}