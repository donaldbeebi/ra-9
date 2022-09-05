#include "StickGameScreen.h"

StickGameScreen::StickGameScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM)
	: Screen(resolution, gameState, screenRemote, AI, SM) {
	m_Background.setTexture(TextureManager::getTexture("graphics/backgrounds/bar_background.png"));
	m_Table.setTexture(TextureManager::getTexture("graphics/backgrounds/bar_table.png"));
	m_Fader = std::make_shared<Fader>(resolution);

	//Loading objects
	m_GameObjects = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();

	for (int i = 0; i < 21; i++) {
		auto temp = std::make_shared<Stick>("stick_" + i, Vector2f(480 + i * 48, 648));
		m_GameObjects->push_back(temp);
	}
	(*m_GameObjects)[18]->getGC()->setState(1);
	(*m_GameObjects)[19]->getGC()->setState(1);
	(*m_GameObjects)[20]->getGC()->setState(2);

	m_GameMaster = std::make_shared<GameMaster>(m_GameObjects, m_AI, m_GameState);
	m_Commander = std::make_shared<StickGameCommander>(m_GameMaster, m_AI, m_GameState, m_ScreenRemote, m_Fader);
	m_PM = std::make_shared<StickGamePanelManager>(m_Commander, m_Resolution);
	m_InputHandler = std::make_unique<StickGameInputHandler>(m_Commander, m_PM, m_GameMaster);
	m_Started = false;

}

void StickGameScreen::initialize() {
	m_GameMaster->startGame();
	if (!m_Started) {
		SoundManager::startJukeBox();
		m_Started = true;
	}
	SoundManager::unmuteJukeBox();
	SoundManager::updateJukeBoxStickGame();
}

void StickGameScreen::update(float dt) {
	Screen::update(dt);
	
	m_GameMaster->update();
	
	auto it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		(*it)->update(dt);
	}

	it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		(*it)->updateGC(dt);
	}
	m_AI->updateStickGame(dt);
}

void StickGameScreen::draw(RenderWindow& window) {
	window.setView(m_View);
	window.draw(m_Background);
	m_AI->getBigGC()->draw(window);
	window.draw(m_Table);

	auto it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		(*it)->draw(window);
	}

	//Debug
	it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		//(*it)->drawTC(window);
	}

	m_Fader->draw(window);

	Screen::draw(window);
}