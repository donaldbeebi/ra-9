#include "InputHandler.h"

using namespace sf;

InputHandler::InputHandler(std::shared_ptr<PanelManager> PM) {
	m_PM = PM;
	m_AlreadyPushingInteract = false;
}

void InputHandler::handleInput(RenderWindow& window) {
	if (m_PM->hasNoOpenPanels()) {
		handleScreenInput(window);
	}
	else {
		handlePanelInput(window);
	}
}

void InputHandler::handlePanelInput(RenderWindow& window) {
	Event event;
	while(window.pollEvent(event)) {
		switch (event.type) {
			/***********************
			****Handle Key Press****
			***********************/
		case Event::KeyPressed:
			switch (event.key.code) {
				//EXIT PANEL
			case Keyboard::Escape:
				window.close();
				break;
			case Keyboard::RShift:
				handleEscapePanel();
				break;

				//PREVIOUS BUTTON
			case Keyboard::W:
			case Keyboard::A:
				m_PM->getCurrentPanel()->getSelector()->previousButton();
				break;

				//NEXT BUTTON
			case Keyboard::S:
			case Keyboard::D:
				m_PM->getCurrentPanel()->getSelector()->nextButton();
				break;

				//PUSH BUTTON
			case Keyboard::Enter:
				m_PM->getCurrentPanel()->getSelector()->pushButton();
				break;
				
			default:
				break;
			}
			break;

			/***********************
			***Handle Key Release***
			***********************/
		case Event::KeyReleased:
			switch(event.key.code){
			case Keyboard::Enter:
				if (m_AlreadyPushingInteract) m_AlreadyPushingInteract = false;
				else m_PM->getCurrentPanel()->getSelector()->releaseButton();
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}

}