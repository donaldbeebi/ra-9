#pragma once
#include <string>

class StickGame {
private:
	bool m_PlayerTurn;
	int m_MaximumStickNumber;
	int m_CurrentStickNumber;
	bool m_GameOver;

	int m_SticksRemoved;

public:
	StickGame();
	bool playerTurn();
	void removeSticks(int numberOfSticks);
	int sticksRemoved();
	int numberOfSticksLeft();
	void endTurn();
	bool isGameOver();
	bool playerWin();
	void restartMatch();

};