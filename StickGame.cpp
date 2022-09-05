#include "StickGame.h"

StickGame::StickGame() {
	m_MaximumStickNumber = 21;
	m_PlayerTurn = true;
	m_CurrentStickNumber = m_MaximumStickNumber;
	m_GameOver = false;

	m_SticksRemoved = 0;
}

bool StickGame::playerTurn() {
	return m_PlayerTurn;
}

void StickGame::removeSticks(int numberOfSticks) {
	if (numberOfSticks > m_CurrentStickNumber) {
		m_SticksRemoved = 0;
	}
	else {
		m_CurrentStickNumber -= numberOfSticks;
		m_SticksRemoved = numberOfSticks;
	}
}

int StickGame::sticksRemoved() {
	return m_SticksRemoved;
}

int StickGame::numberOfSticksLeft() {
	return m_CurrentStickNumber;
}

void StickGame::endTurn() {
	if (m_CurrentStickNumber != 0) {
		m_PlayerTurn = !m_PlayerTurn;
	}
	else m_GameOver = true;
}

bool StickGame::isGameOver() {
	return m_GameOver;
}

bool StickGame::playerWin() {
	return !m_PlayerTurn && m_GameOver;
}

void StickGame::restartMatch() {
	m_CurrentStickNumber = m_MaximumStickNumber;
	m_GameOver = false;
	m_PlayerTurn = true;
}