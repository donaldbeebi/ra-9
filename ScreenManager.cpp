#include "ScreenManager.h"

ScreenManager::ScreenManager(Vector2f resolution, RenderWindow& window) : m_Window(window), m_Fader(resolution) {
	m_Resolution = resolution;
	m_CurrentScreen = "TitleScreen";
	m_View.setSize(resolution);
	m_View.setCenter(resolution / 2.0f);
	m_GameState = std::make_shared<GameState>();
	m_AI = std::make_shared<AI>("RA 9", Vector2f(0.0f, 0.0f), m_GameState); 
	m_ScreenRemote = std::make_shared<ScreenRemote>();
	m_SM = std::make_shared<SoundManager>();
	m_Screens["TitleScreen"] = std::make_unique<TitleScreen>(resolution, m_GameState, m_ScreenRemote, m_AI, m_SM);
	m_Screens["StickGame"] = std::make_unique<StickGameScreen>(resolution, m_GameState, m_ScreenRemote, m_AI, m_SM);
	m_Screens["Cyberspace"] = std::make_unique<GameScreen>(resolution, m_GameState, m_ScreenRemote, m_AI, m_SM);
	m_Screens["Battle"] = std::make_unique<BattleScreen>(resolution, m_GameState, m_ScreenRemote, m_AI, m_SM);
	m_Screens[m_CurrentScreen]->initialize();
}

void ScreenManager::actRemote() {
	if (!m_Fader.isActive()) {
		if (!m_Fader.isBlack()) {
			m_CurrentAction = m_ScreenRemote->getAction();
			if (m_CurrentAction != "none") {
				m_Fader.fadeOut();
			}
		}
		else {
			if (m_CurrentAction != "exit") {
				m_CurrentScreen = m_CurrentAction;
				m_Screens[m_CurrentScreen]->initialize();
				m_Fader.fadeIn();
			}
			else m_Window.close();
		}
	}
	else {
		m_ScreenRemote->getAction(); //this ignores any further request when the screen is doing stuff
	}
}

void ScreenManager::handleInput() {
	m_Screens[m_CurrentScreen]->handleInput(m_Window);
}

void ScreenManager::update(float dt) {
	m_Screens[m_CurrentScreen]->update(dt);
	actRemote();
	m_Fader.update(dt);
	SoundManager::update(dt);
}

void ScreenManager::draw() {
	m_Screens[m_CurrentScreen]->draw(m_Window);
	m_Window.setView(m_View);
	m_Fader.draw(m_Window);
}