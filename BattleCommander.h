#pragma once
#include "Commander.h"
#include "AI.h"
#include "Judge.h"
#include "TremblingComponent.h"

class BattleCommander : public Commander {
private:
	std::shared_ptr<AI> m_AI;
	std::shared_ptr<Judge> m_Judge;

public:
	BattleCommander(std::shared_ptr<Judge> judge, std::shared_ptr<AI> AI, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote);

	virtual void actPanel(std::string action) override;
	void actAI(std::string action);
	virtual std::string getPanelAction() override;
	virtual DialogueLine getDialogueLine() override;

	void update();

	void returnToMainMenu();
};