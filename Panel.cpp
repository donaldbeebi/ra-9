#include "Panel.h"

Panel::Panel(std::string background, Vector2f centerPosition, Vector2f resolution) {
	m_HasButtons = false;
	m_HasSelector = false;
	m_HasDialogueBox = false;
	m_HasPortrait = false;
	m_HasShaker = false;
	m_Action = "none";
	m_AwaitingMenuResponse = false;
	m_Command = "none";
	m_Ready = false;

	Texture& tempTexture = TextureManager::getTexture("graphics/panels/" + background + ".png");
	Vector2f size;
	size.x = tempTexture.getSize().x;
	size.y = tempTexture.getSize().y;

	m_Background.setTexture(tempTexture);
	m_View.setSize(size);
	m_View.setCenter(size.x / 2, size.y / 2);
	
	//Calculation for setting the viewport
	float viewportRelativePositionX = (centerPosition.x - (size.x / 2.0f)) / resolution.x;
	float viewportRelativePositionY = (centerPosition.y - (size.y / 2.0f)) / resolution.y;
	float viewportScaleX = size.x / resolution.x;
	float viewportScaleY = size.y / resolution.y;

	m_View.setViewport(FloatRect(viewportRelativePositionX, viewportRelativePositionY, viewportScaleX, viewportScaleY));
}

void Panel::update(float dt) {
	m_Ready = true;
	if (m_HasDialogueBox) {
		m_DialogueBox->update(dt);
	}
	if (m_HasSelector) {
		actSelector(m_Selector->getAction());
	}
	if (m_HasDialogueBox) {
		actDialogue(m_DialogueBox->getAction());
	}
	if (m_HasShaker) {
		m_Shaker->update(dt);
	}
}

void Panel::draw(RenderWindow& window) {
	//POTENTIAL BUG - I am not sure if I should set view if it is not hidden or set view regardless of the hidden status
	window.setView(m_View);
	if (!m_Hidden) {
		window.draw(m_Background);
		if (m_HasDialogueBox) {
			m_DialogueBox->draw(window);
		}
		if (m_Ready) {			//was (m_Ready)
			if (m_HasButtons) {
				auto it = m_Buttons->begin();
				for (it; it != m_Buttons->end(); it++) {
					(*it)->draw(window);
				}
			}
			if (m_HasPortrait) {
				m_Portrait->draw(window);
			}
			if (m_HasSelector) {
				m_Selector->draw(window);
			}
		}
	}
}
void Panel::show() {
	m_Hidden = false;
}

void Panel::hide() {
	m_Hidden = true;
	m_Ready = false;
}

void Panel::close() {
	hide();
	m_Selector->resetCursor();
	if (!m_ButtonGroups.empty()) {
		switchButtonGroup(0);
	}
	if (m_HasDialogueBox) {
		m_DialogueBox->reset(); //POTENTIAL BUG (showing the text before closing the panel)
	}
}

bool Panel::isHidden() {
	return m_Hidden;
}

void Panel::setCommand(std::string command) {
	m_Command = command;
	m_AwaitingMenuResponse = true;
}

void Panel::switchButtonGroup(int group) {
	for (auto it = m_Buttons->begin(); it != m_Buttons->end(); it++) {
		(*it)->hide();
	}
	for (int i = 0; i != m_ButtonGroups[group].size(); i++) {
		(*m_Buttons)[m_ButtonGroups[group][i]]->show();
	}
	m_Selector->resetCursor();
}

std::string Panel::getAction() {
	if (m_Action != "none") {
		std::string temp = m_Action;
		m_Action = "none";
		return temp;
	}
	return m_Action;
}

std::shared_ptr<std::vector<std::shared_ptr<Button>>> Panel::getButtons() {
	if (m_HasButtons) {
		return m_Buttons;
	}
	else {
		return nullptr;
	}
}

std::shared_ptr<Selector> Panel::getSelector() {
	if (m_HasSelector) {
		return m_Selector;
	}
	else {
		return nullptr;
	}
}

std::shared_ptr<DialogueBox> Panel::getDialogueBox() {
	if (m_HasDialogueBox) {
		return m_DialogueBox;
	}
	else {
		return nullptr;
	}
}

std::shared_ptr<Shaker> Panel::getShaker() {
	return m_Shaker;
}

bool Panel::hasDialogueBox() {
	return m_HasDialogueBox;
}

bool Panel::hasShaker() {
	return m_HasShaker;
}