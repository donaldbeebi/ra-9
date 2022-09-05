#include "GameCommander.h"

void GameCommander::updateGameState() {
	if (!m_GameState->getPuzzleState(1) && findPuzzle("light_switch_puzzle")->isComplete()) {
		m_GameState->setPuzzleState(1, true);
	}
	if (!m_GameState->getPuzzleState(2) && findPuzzle("number_puzzle")->isComplete()) {
		m_GameState->setPuzzleState(2, true);
	}
	if (!m_GameState->getPuzzleState(3) && findPuzzle("key_puzzle")->isComplete()) {
		m_GameState->setPuzzleState(3, true);
	}
}