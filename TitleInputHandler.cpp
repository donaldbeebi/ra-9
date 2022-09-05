#include "TitleInputHandler.h"

TitleInputHandler::TitleInputHandler(std::shared_ptr<PanelManager> PM) : InputHandler(PM) {}

void TitleInputHandler::handleButtonInput(std::string action, RenderWindow& window) {
	if (action == "start") {
		//std::cout << "start" << std::endl;
	}
	if (action == "exit") {
		window.close();
	}
	if (action == "return") {
		//m_PM->closeCurrentPanel();
	}
	if (action == "option") {
		//m_PM->openPanel("option");
	}
	if (action == "text_speed") {
		//m_PM->switchPanel("test");
	}
}

void TitleInputHandler::handleEscapePanel() {
	//do nothing
}