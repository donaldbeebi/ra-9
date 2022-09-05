#include "StickGameInputHandler.h"

StickGameInputHandler::StickGameInputHandler(std::shared_ptr<StickGameCommander> commander, std::shared_ptr<PanelManager> PM, std::shared_ptr<GameMaster> gameMaster)
	: InputHandler(PM) {
	m_Commander = commander;
	m_GameMaster = gameMaster;
}

void StickGameInputHandler::handleScreenInput(RenderWindow& window) {
	/***********************
	******Event Polling*****
	***********************/
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			/***********************
			****Handle Key Press****
			***********************/
		case Event::KeyPressed:
			switch (event.key.code) {
			case Keyboard::Escape:
				window.close();
				break;
			}
			break;

			/***********************
			***Handle Key Release***
			***********************/
		case Event::KeyReleased:
			switch (event.key.code) {
			}
			break;
		}
	}
}

void StickGameInputHandler::handleEscapePanel() {
	phase temp = m_GameMaster->getCurrentPhase();
	if (temp == phase::stick || temp == phase::chat || temp == phase::other) {
		m_PM->closeCurrentPanel();
		m_Commander->returnToMainMenu();
	}
}