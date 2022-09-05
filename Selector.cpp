#include "Selector.h"

void Selector::setCursor() {
	//Calculation of the origin
	m_CursorSprite.setPosition(((*m_Buttons)[m_CurrentButton])->getCursorCenterPosition());
}

void Selector::resetCursor() {
	m_Hidden = true;
	for (int i = 0; i != m_NumOfButtons; i++) {
		if (!(*m_Buttons)[i]->isHidden()) {
			m_CurrentButton = i;
			setCursor();
			m_Hidden = false;
			break;
		}
	}
}

Selector::Selector(std::shared_ptr<std::vector<std::shared_ptr<Button>>> buttons) {
	m_Buttons = buttons;
	m_NumOfButtons = m_Buttons->size();
	m_CurrentButton = 0;
	m_ButtonPressed = false;
	m_CursorSprite.setTexture(TextureManager::getTexture("graphics/panels/selector_cursor.png"));
	int originX = m_CursorSprite.getLocalBounds().width / 2;
	int originY = m_CursorSprite.getLocalBounds().height;
	m_CursorSprite.setOrigin(Vector2f(originX, originY));
	m_Hidden = false;
	resetCursor();
}

void Selector::previousButton() {
	if (!m_Hidden) {
		int temp = m_CurrentButton;
		if (!m_ButtonPressed) {
			while (temp != 0) {
				temp--;
				if (!(*m_Buttons)[temp]->isHidden()) {
					m_CurrentButton = temp;
					break;
				}
			}
			setCursor();
		}
	}
}

void Selector::nextButton() {
	if (!m_Hidden) {
		int temp = m_CurrentButton;
		if (!m_ButtonPressed) {
			while (temp != m_NumOfButtons - 1) {
				temp++;
				if (!(*m_Buttons)[temp]->isHidden()) {
					m_CurrentButton = temp;
					break;
				}
			}
			setCursor();
		}
	}
}

void Selector::pushButton() {
	m_ButtonPressed = true;
	(*m_Buttons)[m_CurrentButton]->push();
}

void Selector::releaseButton() {
	m_ButtonPressed = false;
	(*m_Buttons)[m_CurrentButton]->release();
}

std::string Selector::getAction() {
	auto it = m_Buttons->begin();
	for (it; it != m_Buttons->end(); it++) {
		std::string temp = (*it)->getAction();
		if (temp != "none") {
			return temp;
		}
	}
	return "none";
}

void Selector::draw(RenderWindow& window) {
	if (!m_Hidden) {
		window.draw(m_CursorSprite);
	}
}