#include "GameState.h"

GameState::GameState() {
	m_Action = "";

	m_PlayerName = "";

	m_LightState = true;
	m_PuzzleOneComplete = false;
	m_PuzzleTwoComplete = false;
	m_PuzzleThreeComplete = false;
	m_GotKey = false;
	m_GotKeycard = false;
	m_BigButtonPushed = false;
	m_ChallengeDecision = false;
	m_AIChallenged = false;
	m_AIDefeated = false;
	m_AIKilled = false;
	m_PlayerKilled = false;
	m_AISpared = false;
	m_AISaved = false;
	m_CyberspaceTravelled = false;
	m_PlayerWantsToHelp = false;
	m_AIAngered = false;

	m_Scene = 0;

	m_GameStarted = false;
}

/********************************
************ Setters ************
********************************/

void GameState::startGame() {
	m_GameStarted = true;
}

void GameState::setPlayerName(std::string name) {
	m_PlayerName = name;
}

void GameState::setLightState(bool state) {
	m_LightState = state;
}

void GameState::setPuzzleState(int puzzle, bool state) {
	switch (puzzle) {
	case 1:
		m_PuzzleOneComplete = state;
		m_Action = "puzzle_one_complete";
		break;
	case 2:
		m_PuzzleTwoComplete = state;
		m_Action = "puzzle_two_complete";
		break;
	case 3:
		m_PuzzleThreeComplete = state;
		m_Action = "puzzle_three_complete";
		break;
	}
}

void GameState::getKey() {
	m_GotKey = true;
}

void GameState::getKeycard() {
	m_GotKeycard = true;
}

void GameState::pushBigButton() {
	m_BigButtonPushed = true;
}

void GameState::challengeAI() {
	m_ChallengeDecision = true;
	m_AIChallenged = true;
}

void GameState::dontChallengeAI() {
	m_ChallengeDecision = true;
	m_AIChallenged = false;
}

void GameState::defeatAI() {
	m_AIDefeated = true;
}

void GameState::spareAI() {
	m_AISpared = true;
}

void GameState::killAI() {
	m_AIKilled = true;
}

void GameState::saveAI() {
	m_AISaved = true;
}

void GameState::travelToCyberspace() {
	m_CyberspaceTravelled = true;
}

void GameState::helpAI() {
	m_PlayerWantsToHelp = true;
}

void GameState::angerAI() {
	m_AIAngered = true;
}

void GameState::nextScene() {
	m_Scene++;

}

void GameState::actCommander(std::string action) {
}

/********************************
************ Getters ************
********************************/

std::string GameState::getPlayerName() {
	return m_PlayerName;
}

bool GameState::gameStarted() {
	return m_GameStarted;
}

bool GameState::getLightState() {
	return m_LightState;
}

bool GameState::getPuzzleState(int puzzle) {
	switch (puzzle) {
	case 1:
		return m_PuzzleOneComplete;
	case 2:
		return m_PuzzleTwoComplete;
	case 3:
		return m_PuzzleThreeComplete;
	default:
		return false;
	}
}

bool GameState::gotKey() {
	return m_GotKey;
}

bool GameState::gotKeycard() {
	return m_GotKeycard;
}

bool GameState::bigButtonPushed() {
	return m_BigButtonPushed;
}

bool GameState::challengeDecisionMade() {
	return m_ChallengeDecision;
}

bool GameState::AIChallenged() {
	return m_AIChallenged;
}

bool GameState::AIDefeated() {
	return m_AIDefeated;
}

bool GameState::AISpared() {
	return m_AISpared;
}

bool GameState::AIKilled() {
	return m_AIKilled;
}

bool GameState::AISaved() {
	return m_AISaved;
}

bool GameState::cyberspaceTravelled() {
	return m_CyberspaceTravelled;
}

bool GameState::playerWantsToHelp() {
	return m_PlayerWantsToHelp;
}

bool GameState::AIAngered() {
	return m_AIAngered;
}

int GameState::getScene() {
	return m_Scene;
}

std::string GameState::getAction() {
	std::string temp = m_Action;
	m_Action = "none";
	return temp;
}