#include "BattleScreen.h"

BattleScreen::BattleScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM)
	: Screen(resolution, gameState, screenRemote, AI, SM) {
	m_Judge = std::make_shared<Judge>(m_AI);
	m_Commander = std::make_shared<BattleCommander>(m_Judge, m_AI, m_GameState, m_ScreenRemote);
	m_PM = std::make_shared<BattlePanelManager>(m_Commander, m_Resolution);
	m_InputHandler = std::make_unique<BattleInputHandler>(m_Commander, m_PM, m_Judge);
}

void BattleScreen::initialize() {
	m_Judge->startGame();
	m_AI->prepareForBattle(m_PM);
	SoundManager::stopJukeBox();
	SoundManager::playBossTrack();
}

void BattleScreen::update(float dt) {
	Screen::update(dt);
	m_Judge->update();
	m_AI->updateBattle(dt);
	m_Commander->update();
}

void BattleScreen::draw(RenderWindow& window) {
	window.setView(m_View);
	m_AI->getFightGC()->draw(window);
	Screen::draw(window);
}