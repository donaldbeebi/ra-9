#pragma once
#include "Trigger.h"

class GameStateTrigger : public Trigger {
private:
	std::shared_ptr<GameState> m_GameState;
	std::string m_Target;
	int m_State;

public:
	GameStateTrigger(std::shared_ptr<GameState> gameState, std::string target) {
		m_GameState = gameState;
		m_Target = target;
	}
	virtual void update() {
		if (m_Active) {
			if (m_Target.find("puzzle") != std::string::npos) {
				if (m_GameState->getPuzzleState(m_Target.back() - '0')) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "key") {
				if (m_GameState->gotKey()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "keycard") {
				if (m_GameState->gotKeycard()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "bigbutton") {
				if (m_GameState->bigButtonPushed()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "challenged") {
				if (m_GameState->AIChallenged() && m_GameState->challengeDecisionMade()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "notchallenged") {
				if (!m_GameState->AIChallenged() && m_GameState->challengeDecisionMade()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "lightoff") {
				if (!m_GameState->getLightState()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "defeated") {
				if (m_GameState->AIDefeated()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "spared") {
				if (m_GameState->AISpared()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
			else if (m_Target == "killed") {
				if (m_GameState->AIKilled()) {
					m_Triggered = true;
					m_Active = false;
				}
			}
		}
	}
};