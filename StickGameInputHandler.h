#pragma once
#include "InputHandler.h"
#include "StickGameCommander.h"
#include "GameMaster.h"

class StickGameInputHandler : public InputHandler {
private:
	std::shared_ptr<StickGameCommander> m_Commander;
	std::shared_ptr<GameMaster> m_GameMaster;

public:
	StickGameInputHandler(std::shared_ptr<StickGameCommander> commander, std::shared_ptr<PanelManager> PM, std::shared_ptr<GameMaster> gameMaster);

	virtual void handleScreenInput(RenderWindow& window);
	virtual void handleEscapePanel() override;
};