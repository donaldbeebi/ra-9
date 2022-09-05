#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(unsigned int stateCount) {
	m_Enabled = true;
	m_DrawOffsetY = 0.0f;
	m_TextRectOffsetY = 0.0f;
	m_State = 0;
	m_StateCount = stateCount;
}

void GraphicsComponent::enable() {
	m_Enabled = true;
}

void GraphicsComponent::disable() {
	m_Enabled = false;
}

void GraphicsComponent::toggle() {
	m_Enabled = !m_Enabled;
}

void GraphicsComponent::toggleState(int state1, int state2) {
	if (m_State == state1) m_State = state2;
	else m_State = state1;
	m_TextRectOffsetY = m_State * int(m_TextureSize.y);
}

bool GraphicsComponent::isEnabled() {
	return m_Enabled;
}

void GraphicsComponent::setState(int state) {
	m_TextRectOffsetY = state * int(m_TextureSize.y);
	m_State = state;
}

Vector2f GraphicsComponent::getSize() {
	return m_TextureSize;
}

int GraphicsComponent::getState() {
	return m_State;
}

unsigned int GraphicsComponent::getStateCount() {
	return m_StateCount;
}

Vector2f GraphicsComponent::getSpritePosition() {
	return m_Sprite.getPosition();
}

void GraphicsComponent::update(float dt) {
	m_Sprite.setTextureRect(IntRect(m_TextRect.left, m_TextRect.top + m_TextRectOffsetY, m_TextRect.width, m_TextRect.height));
	//m_Sprite.setPosition(Vector2f(round(m_TC->getDrawPosition().x), round(m_TC->getDrawPosition().y - m_DrawOffsetY)));
	m_Sprite.setPosition(Vector2f(m_TC->getDrawPosition().x, m_TC->getDrawPosition().y - m_DrawOffsetY));
	//m_Sprite.setPosition(Vector2f(m_TC->getDrawPosition().x, m_TC->getDrawPosition().y));
}

void GraphicsComponent::draw(RenderWindow& window) {
	if (m_Enabled) {
		window.draw(m_Sprite);
	}
}