#include "GameEngine.h"

GameEngine::GameEngine() {
	m_Resolution.x = 1920.0f;//VideoMode::getDesktopMode().width;
	m_Resolution.y = 1080.0f;//VideoMode::getDesktopMode().height;
	m_Window.create(VideoMode(m_Resolution.x, m_Resolution.y), "RA 9", Style::Fullscreen);
	//m_Window.setFramerateLimit(60);
	m_Window.setVerticalSyncEnabled(true);
	m_Window.setKeyRepeatEnabled(false);
	m_ScreenManager = std::make_unique<ScreenManager>(m_Resolution, m_Window);
}

void GameEngine::run() {
	/**************************
	Things here run every frame
	**************************/
	while (m_Window.isOpen()) {
		m_DT = m_Clock.restart();
		handleInput();
		update();
		draw();
	}

}

void GameEngine::handleInput() {
	m_ScreenManager->handleInput();
}

void GameEngine::update() {
	m_ScreenManager->update(m_DT.asSeconds());
}

void GameEngine::draw() {
	m_Window.clear(Color::Black);
	m_ScreenManager->draw();
	m_Window.display();
}

