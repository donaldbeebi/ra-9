#pragma once
#include "Portrait.h"

Portrait::Portrait(Vector2f initialPosition) {
	m_State = 0;
	m_MaxStates = 7;
	m_Sprite.setTexture(TextureManager::getTexture("graphics/panels/AIportraits/portrait.png"));
	m_TextRect.left = 0;
	m_TextRect.top = 0;
	m_TextRect.width = 200;
	m_TextRect.height = 200;
	m_Sprite.setTextureRect(m_TextRect);
	m_Sprite.setPosition(initialPosition);

	m_Showing = false;
}

void Portrait::setPortrait(int state) {
	if (state > -1 && state < m_MaxStates) {
		m_State = state;
		m_TextRect.top = m_State * 200;
		m_Sprite.setTextureRect(m_TextRect);
	}
}

void Portrait::show() {
	m_Showing = true;
}

void Portrait::hide() {
	m_Showing = false;
}

bool Portrait::isShowing() {
	return m_Showing;
}

void Portrait::draw(RenderWindow& window) {
	if (m_Showing) {
		window.draw(m_Sprite);
	}
}