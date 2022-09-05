#include "GameInputHandler.h"

GameInputHandler::GameInputHandler(std::shared_ptr<PanelManager> PM, std::shared_ptr<GameCommander> commander)
	: InputHandler(PM){
	m_Commander = commander;
}

void GameInputHandler::handlePanelInput(RenderWindow& window) {
	InputHandler::handlePanelInput(window);
	if (m_AlreadyPushingInteract) {
		m_Commander->releaseInteraction();
	}
}

void GameInputHandler::handleScreenInput(RenderWindow& window) {
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
			case Keyboard::Enter:
				m_Commander->pushInteraction();
				m_AlreadyPushingInteract = true;
				break;
			case Keyboard::Tab:
				m_PM->openPanel("menu");
				break;
			}
			break;

			/***********************
			***Handle Key Release***
			***********************/
		case Event::KeyReleased:
			switch (event.key.code) {
			case Keyboard::Enter:
				m_AlreadyPushingInteract = false;
				m_Commander->releaseInteraction();
				break;
			}
			break;
		}
	}

	/***********************
	*****Keyboard Input*****
	***********************/
	if (Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S)) {
		m_Commander->movePlayer(Direction::up);
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W)) {
		m_Commander->movePlayer(Direction::down);
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D)) {
		m_Commander->movePlayer(Direction::left);
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A)) {
		m_Commander->movePlayer(Direction::right);
	}
}

void GameInputHandler::handleEscapePanel() {
}