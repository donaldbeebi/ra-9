#pragma once
#include "InputHandler.h"

class TitleInputHandler : public InputHandler {
public:
	TitleInputHandler(std::shared_ptr<PanelManager> PM);

	void handleButtonInput(std::string action, RenderWindow& window) override;
	void handleEscapePanel() override;
};