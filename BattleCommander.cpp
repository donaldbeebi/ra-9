#include "BattleCommander.h"

BattleCommander::BattleCommander(std::shared_ptr<Judge> judge, std::shared_ptr<AI> AI, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote)
	: Commander(gameState, screenRemote) {
	m_AI = AI;
	m_Judge = judge;
}

void BattleCommander::actPanel(std::string action) {
	if (action == "command_player_defeated") {
		m_ScreenRemote->exitGame();
	}
	else if (action == "command_hurt_AI") {
		m_AI->getFightGC()->setState(1);
		m_Judge->act(0);
		m_AI->getTrC()->trigger();
		SoundManager::play("hitAI");
		SoundManager::stopBossTrack();
	}
	else if (action == "command_make_AI_kneel") {
		m_AI->getFightGC()->setState(2);
		m_Judge->act(0);
		m_GameState->defeatAI();
	}
	else if (action == "command_tremble") {
		m_AI->getTrC()->trigger();
	}
	else if (action == "command_final_decision_0") {
		m_AI->getTrC()->triggerBig();
		SoundManager::play("hitAIcritical");
		m_GameState->killAI();
	}
	else if (action == "command_final_decision_1") {
		m_GameState->spareAI();
	}
	else if (action.find("command") != std::string::npos) {
		m_Judge->act(action.back() - '0');
	}
}

void BattleCommander::actAI(std::string action) {
	if (action == "command_AI_defeat_speech_finish") {
		m_Judge->triggerStage(stage::kill);
	}
	else if (action == "command_AI_final_speech_finish") {
		m_ScreenRemote->switchScreen("TitleScreen");
	}
}

std::string BattleCommander::getPanelAction() {
	return "none";
}

DialogueLine BattleCommander::getDialogueLine() {
	DialogueLine temp = m_Judge->getDialogueLine();
	if (temp.line != "none") {
		temp.speaker = "none";
		return temp;
	}
	temp = m_AI->getFightChat()->getDialogueLine();
	if (temp.line != "none") {
		return temp;
	}
	return DialogueLine("none", "none");
}

void BattleCommander::update() {
	actAI(m_AI->getAction());
}

void BattleCommander::returnToMainMenu() {
	m_Judge->returnToMainMenu();
}