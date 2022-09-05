#pragma once
#include "Trigger.h"

class GameStartTrigger : public Trigger {
private:
	std::shared_ptr<GameState> m_GameState;

public:
	GameStartTrigger(std::shared_ptr<GameState> gameState) {
		m_GameState = gameState;
	}

	virtual void update() {
		if (m_Active) {
			if (m_GameState->gameStarted()) {
				m_Triggered = true;
				m_Active = false;
			}
		}
	}
};