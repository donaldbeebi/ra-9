#include "BattleInputHandler.h"

BattleInputHandler::BattleInputHandler(std::shared_ptr<BattleCommander> commander, std::shared_ptr<PanelManager> PM, std::shared_ptr<Judge> judge) 
	: InputHandler(PM) {
	m_Commander = commander;
	m_Judge = judge;
}

void BattleInputHandler::handleScreenInput(RenderWindow& window) {
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

void BattleInputHandler::handleEscapePanel() {
	stage temp = m_Judge->getCurrentStage();
	if (temp == stage::fight || temp == stage::item) {
		m_PM->closeCurrentPanel();
		m_Commander->returnToMainMenu();
	}
}