#pragma once
#include "Commander.h"
#include "GameMaster.h"

class StickGameCommander : public Commander {
private:
	std::shared_ptr<GameMaster> m_GameMaster;
	std::shared_ptr<Fader> m_Fader;
	std::shared_ptr<AI> m_AI;

public:
	StickGameCommander(std::shared_ptr<GameMaster> gameMaster, std::shared_ptr<AI> AI, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<Fader> fader);

	virtual void actPanel(std::string action) override; //panel to commander
	virtual std::string getPanelAction() override; //feedback
	virtual DialogueLine getDialogueLine() override;

	void returnToMainMenu();
};