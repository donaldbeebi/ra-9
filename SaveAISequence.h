#pragma once
#include "ScreenRemote.h"
#include "Fader.h"
#include "GameState.h";
#include "SoundManager.h"
#include "Shaker.h"
#include "ScreenShaker.h"
#include <memory>

class SaveAISequence {
private:
	std::shared_ptr<Fader> m_BlackFader;
	std::shared_ptr<Fader> m_WhiteFader;
	std::shared_ptr<ScreenRemote> m_ScreenRemote;
	std::shared_ptr<GameState> m_GameState;
	std::shared_ptr<Shaker> m_Shaker;
	bool m_Triggered;
	int m_Stage;
	float m_CurrentTime;
	float m_WaitTime;

public:
	SaveAISequence(std::shared_ptr<Fader> blackFader, std::shared_ptr<Fader> whiteFader, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<GameState> gameState, std::shared_ptr<Shaker> shaker) {
		m_BlackFader = blackFader;
		m_WhiteFader = whiteFader;
		m_ScreenRemote = screenRemote;
		m_GameState = gameState;
		m_Shaker = shaker;
		m_Triggered = false;
		m_Stage = 0;
		m_CurrentTime = 0.0f;
		m_WaitTime = 6.0f;
	}

	void trigger() { m_Triggered = true; }

	void update(float dt) {
		if (m_Triggered) {
			switch (m_Stage) {
			case 0:
				SoundManager::play("riser");
				m_WhiteFader->fadeOut();
				m_Shaker->start();
				m_GameState->saveAI();
				m_Stage++;
				break;
			case 1:
				if (m_WhiteFader->isBlack()) {
					SoundManager::stopAlarm();
					m_Shaker->stop();
					m_Stage++;
				}
				break;
			case 2:
				m_BlackFader->fadeOut();
				m_Stage++;
				break;
			case 3:
				m_CurrentTime += dt;
				if (m_CurrentTime > m_WaitTime) {
					m_CurrentTime = 0.0f;
					m_Stage++;
				}
				break;
			case 4:
				m_ScreenRemote->switchScreen("TitleScreen");
				m_Stage++;
				break;
			case 5:
				m_CurrentTime += dt;
				if (m_CurrentTime > 2.0f) {
					m_CurrentTime = 0.0f;
					m_BlackFader->fadeIn();
					m_Triggered = false;
					m_Stage = 0;
				}
				break;
			}
		}
	}
};