#include "Screen.h"

Screen::Screen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM) {
	m_GameState = gameState;
	m_Fader = std::make_shared<Fader>(resolution);
	m_Resolution = resolution;
	m_View.setSize(resolution.x, resolution.y);
	m_View.setCenter(resolution.x / 2.0f, resolution.y / 2.0f);
	m_Panels = std::make_shared<std::map<std::string, std::shared_ptr<Panel>>>();
	m_ScreenRemote = screenRemote;
	m_AI = AI;
	m_SM = SM;
}

void Screen::addPanel(std::string name, std::string background, Vector2f centerPosition) {
	(*m_Panels)[name] = std::make_shared<Panel>(background, centerPosition, m_Resolution);
}

void Screen::handleInput(RenderWindow& window) {
	m_InputHandler->handleInput(window);
}

void Screen::update(float dt) {
	m_PM->update(dt);
}

void Screen::draw(RenderWindow& window) {
	//Draw all the panels
	m_PM->draw(window);
}