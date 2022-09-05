#pragma once
#include <ctime>
#include <stdlib.h>
#include "SoundManager.h"

class Battleground {
private:
	int m_AIHealth;
	bool m_DefenseLowered;
	int m_PlayerHealth;
	bool m_PlayerTurn;
	bool m_Item[4];

public:
	Battleground();
	bool isPlayerTurn();

	void lowerDefense();
	bool killAI();
	bool useItem(int item);
	int attackPlayer();
	void endTurn();
	int playerHealth();
	int AIHealth();
	bool gameEnded();
	bool playerWin();

};