#include "TitleCommander.h"

TitleCommander::TitleCommander(std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI)
	: Commander(gameState, screenRemote) {
	m_AI = AI;
	m_DC = std::make_shared<DialogueComponent>("TitleScreen", 0.0f, false);

}

std::string TitleCommander::getPanelAction() {
	return "none";
}

void TitleCommander::actPanel(std::string action) {
	if (action == "play") {
		m_ScreenRemote->switchScreen("StickGame");
	}
	else if (action == "exit") {
		if (!m_GameState->AIKilled() && !m_GameState->AISaved() && !m_GameState->AISpared()) {
			if (m_GameState->playerWantsToHelp()) {
				m_AI->getDC()->trigger("command_confirm_exit_game");
			}
			else if (m_GameState->AIAngered()) {
				m_AI->getDC()->trigger("command_exit_game");
			}
			else m_ScreenRemote->exitGame();
		}
		else m_ScreenRemote->exitGame();
	}
	else if (action == "command_confirm_exit_game") {
		m_DC->trigger("inspect");
	}
	else if (action == "command_exit_game_true") {
		m_ScreenRemote->exitGame();
	}
	else if (action == "command_exit_game") {
		m_ScreenRemote->exitGame();
	}
}


DialogueLine TitleCommander::getDialogueLine() {
	auto temp = m_AI->getDC()->getDialogueLine();
	if (temp.line != "none") {
		return temp;
	}
	else return m_DC->getDialogueLine();
}