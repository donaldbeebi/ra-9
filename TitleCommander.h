#pragma once
#include "Commander.h"
#include "AI.h"

class TitleCommander : public Commander {
private:
	std::shared_ptr<AI> m_AI;
	std::shared_ptr<DialogueComponent> m_DC;

public:
	TitleCommander(std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI);
	virtual std::string getPanelAction() override;
	virtual void actPanel(std::string action) override;
	virtual DialogueLine getDialogueLine() override;
};