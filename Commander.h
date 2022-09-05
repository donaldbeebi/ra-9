#pragma once
#include <iostream>
#include "GameState.h"
#include "Structs.h"
#include <memory>
#include "ScreenRemote.h"
#include "Fader.h"

class Commander {
protected:
	std::shared_ptr<GameState> m_GameState;
	std::shared_ptr<ScreenRemote> m_ScreenRemote;
public:
	Commander(std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote) {
		m_GameState = gameState; m_ScreenRemote = screenRemote;
	}
	virtual std::string getPanelAction() = 0;		//this feeds back to the panel manager
	virtual DialogueLine getDialogueLine() { return DialogueLine("none", "none"); } //REMOVE - not used anymore
	virtual void actPanel(std::string action) = 0;
};