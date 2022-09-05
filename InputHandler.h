#pragma once
#include <iostream>
#include <map>
#include <list>
#include <memory>
#include "PanelManager.h"

using namespace sf;

class InputHandler {
protected:
	bool m_AlreadyPushingInteract;

	std::shared_ptr<PanelManager> m_PM;

public:
	InputHandler(std::shared_ptr<PanelManager> PM);
	//void openPanel(std::string targetPanel);
	//void switchPanel(std::string targetPanel);
	//void closeCurrentPanel();
	void handleInput(RenderWindow& window);
	
	virtual void handlePanelInput(RenderWindow& window);
	virtual void handleScreenInput(RenderWindow& window) {}
	virtual void handleButtonInput(std::string action, RenderWindow& window) {}; //ABANDONED
	virtual void handleEscapePanel() = 0;
};