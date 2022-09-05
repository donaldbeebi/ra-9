#include "TitleScreen.h"

TitleScreen::TitleScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM)
	: Screen(resolution, gameState, screenRemote, AI, SM) {
	m_Background.setTexture(TextureManager::getTexture("graphics/backgrounds/title.png"));
	m_Fader = std::make_shared<Fader>(resolution);

	/*****************
	*****Managers*****
	*****************/
	m_Commander = std::make_shared<TitleCommander>(m_GameState, m_ScreenRemote, m_AI);
	m_PM = std::make_shared<TitlePanelManager>(m_Commander, m_Resolution);
	m_PM->openPanel("title");
	m_InputHandler = std::make_unique<TitleInputHandler>(m_PM);
}

void TitleScreen::update(float dt) {
	Screen::update(dt);
	m_AI->update(dt);
}

void TitleScreen::draw(RenderWindow& window) {
	window.setView(m_View);
	window.draw(m_Background);
	Screen::draw(window);
}

void TitleScreen::initialize() {
	SoundManager::muteJukeBox();
}