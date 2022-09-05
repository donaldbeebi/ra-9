#include "StickGameCommander.h"

StickGameCommander::StickGameCommander(std::shared_ptr<GameMaster> gameMaster, std::shared_ptr<AI> AI, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<Fader> fader)
	: Commander(gameState, screenRemote) {
	m_GameMaster = gameMaster;
	m_Fader = fader;
	m_AI = AI;
}

void StickGameCommander::actPanel(std::string action) {
	if (action.find("command_menu") != std::string::npos) {
		int temp = action.back() - '0';
		if (temp == 3) {
			m_ScreenRemote->switchScreen("TitleScreen");
		}
		else m_GameMaster->act(temp);
	}
	else if (action.find("command_stick") != std::string::npos) {
		m_GameMaster->act(action.back() - '0');
	}
	else if (action == "command_next") {
		m_GameMaster->act(0);
	}
	else if (action == "command_continue_0") {
		m_GameMaster->act(0);
	}
	else if (action == "command_continue_1") {
		m_ScreenRemote->switchScreen("TitleScreen");
	}
	else if (action == "command_other_0") {
		if (m_Fader->isBlack()) {
			m_Fader->brighten();
			m_GameMaster->lightIsOn(true);
			m_GameState->setLightState(true);
		}
		else {
			m_Fader->darken();
			m_GameMaster->lightIsOn(false);
			m_GameState->setLightState(false);
		}
		m_GameMaster->act(0);
	}
	else if (action == "command_other_1") {
		SoundManager::toggleJukeBox();
		m_GameMaster->act(0);
	}
	else if (action.find("command_chat") != std::string::npos) {
		m_GameMaster->act(action.back() - '0');
	}
	else if (action == "command_response") {
		m_GameMaster->triggerPhase(phase::AI);
	}
	else if (action == "command_switch_cyberspace") {
		m_ScreenRemote->switchScreen("Cyberspace");
	}
	else if (action == "command_switch_battle") {
		m_ScreenRemote->switchScreen("Battle");
	}
	else if (action == "command_help_AI") {
		m_GameMaster->act(0);
		m_GameState->helpAI();
	}
	else if (action == "command_anger_AI") {
		m_GameMaster->act(0);
		m_GameState->angerAI();
	}
}

std::string StickGameCommander::getPanelAction() {
	return "none";
}

DialogueLine StickGameCommander::getDialogueLine() {
	DialogueLine temp = m_GameMaster->getDialogueLine();
	if (temp.line != "none") {
		temp.speaker = "none";
		return temp;
	}
	return m_AI->getChatComponent()->getDialogueLine();
}

void StickGameCommander::returnToMainMenu() {
	m_GameMaster->returnToMainMenu();
}