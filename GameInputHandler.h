#pragma once
#include <memory>
#include "InputHandler.h"
#include "Player.h"
#include "GameCommander.h"

class GameInputHandler : public InputHandler {
private:
	std::shared_ptr<GameCommander> m_Commander;

public:
	GameInputHandler(std::shared_ptr<PanelManager> PM, std::shared_ptr<GameCommander> commander);

	virtual void handlePanelInput(RenderWindow& window) override;
	virtual void handleScreenInput(RenderWindow& window) override;
	virtual void handleEscapePanel() override;
};