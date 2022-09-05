#include "Battleground.h"

Battleground::Battleground() {
	m_AIHealth = 10;
	m_DefenseLowered = false;
	m_PlayerHealth = 10;
	m_PlayerTurn = true;
	m_Item[0] = true;
	m_Item[1] = true;
	m_Item[2] = true;
	m_Item[3] = true;
	srand((int)time(0));
}

bool Battleground::isPlayerTurn() {
	return m_PlayerTurn;
}

void Battleground::lowerDefense(){
	m_DefenseLowered = true;
}

bool Battleground::killAI() {
	if (m_DefenseLowered) {
		m_AIHealth = 0;
		return true;
	}
	return false;
}

bool Battleground::useItem(int item) {
	bool temp = m_Item[item];
	switch (item) {
	case 0:
		return true;
		break;
	case 1:
		m_Item[item] = false;
		return temp;
		break;
	case 2:
		if (temp) {
			m_AIHealth -= 1;
		}
		m_Item[item] = false;
		return temp;
		break;
	case 3:
		if (temp) {
			SoundManager::play("heal");
			m_PlayerHealth = 10;
		}
		m_Item[item] = false;
		return temp;
	}
	return false;
}

int Battleground::attackPlayer() {
	int attack = (rand() % 2) + 3;
	m_PlayerHealth -= attack;
	if (m_PlayerHealth < 0) {
		m_PlayerHealth = 0;
	}
	return attack;
}

void Battleground::endTurn() {
	m_PlayerTurn = !m_PlayerTurn;
}

int Battleground::playerHealth() {
	return m_PlayerHealth;
}

int Battleground::AIHealth() {
	return m_AIHealth;
}

bool Battleground::gameEnded() {
	return (m_PlayerHealth <= 0 || m_AIHealth <= 0);
}

bool Battleground::playerWin() {
	return (m_AIHealth <= 0);
}