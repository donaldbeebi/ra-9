#pragma once
#include "InputHandler.h"
#include "BattleCommander.h"
#include "Judge.h"

class BattleInputHandler : public InputHandler {
private:
	std::shared_ptr<BattleCommander> m_Commander;
	std::shared_ptr<Judge> m_Judge;

public:
	BattleInputHandler(std::shared_ptr<BattleCommander> commander, std::shared_ptr<PanelManager> PM, std::shared_ptr<Judge> judge);

	virtual void handleScreenInput(RenderWindow& window);
	virtual void handleEscapePanel() override;
};