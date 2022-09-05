#include "Button.h"

Button::Button(std::string texture, std::string pushAction, std::string releaseAction, Vector2f centerPosition) {
	Texture& tempTexture = TextureManager::getTexture("graphics/panels/buttons/" + texture + ".png");
	
	m_Size.x = tempTexture.getSize().x / 2.0f;
	m_Size.y = tempTexture.getSize().y;

	m_Sprite.setTexture(tempTexture);
	m_Sprite.setTextureRect(IntRect(0, 0, (int)m_Size.x, (int)m_Size.y));
	m_Sprite.setOrigin(m_Size.x / 2, m_Size.y / 2);
	m_Sprite.setPosition(centerPosition);
	m_PushAction = pushAction;
	m_ReleaseAction = releaseAction;
	m_CurrentAction = "none";
	
	//TWEAK - this determines where the cursor is relative to the button
	m_CursorCenterPosition.x = centerPosition.x;
	m_CursorCenterPosition.y = centerPosition.y - m_Size.y / 2 + 2;
	m_Hidden = false;
}

void Button::show() {
	m_Hidden = false;
}

void Button::hide() {
	m_Hidden = true;
}

bool Button::isHidden() {
	return m_Hidden;
}

void Button::setPosition(Vector2f centerPosition) {
	m_Sprite.setPosition(centerPosition);
	m_CursorCenterPosition.x = centerPosition.x;
	m_CursorCenterPosition.y = centerPosition.y - m_Size.y / 2 + 2;
}

Vector2f Button::getCursorCenterPosition() {
	return m_CursorCenterPosition;
}

void Button::push() {
	if (!m_Hidden) {
		m_Sprite.setTextureRect(IntRect(m_Size.x, 0, m_Size.x, m_Size.y));
		m_CurrentAction = m_PushAction;
		SoundManager::play("click");
	}
}

void Button::release() {
	if (!m_Hidden) {
		m_Sprite.setTextureRect(IntRect(0, 0, m_Size.x, m_Size.y));
		m_CurrentAction = m_ReleaseAction;
		SoundManager::play("clock");
	}
}

std::string Button::getAction() {
	if (m_CurrentAction != "none") {
		std::string temp = m_CurrentAction;
		m_CurrentAction = "none";
		return temp;
	}
	else return "none";
}

void Button::draw(RenderWindow& window) {
	if (!m_Hidden) {
		window.draw(m_Sprite);
	}
}