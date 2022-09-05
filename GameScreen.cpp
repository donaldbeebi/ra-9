#include "GameScreen.h"

GameScreen::GameScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM)
	: Screen(resolution, gameState, screenRemote, AI, SM) {
	m_Tilemap = std::make_shared<Tilemap>();
	m_HUD.setSize(resolution);
	m_HUD.setCenter(resolution.x / 2, resolution.y / 2);
	m_WhiteFader = std::make_shared<Fader>(resolution);
	m_WhiteFader->setWhite();
	m_WhiteFader->setTime(7);
	m_Shaker = std::make_shared<Shaker>(m_View);
	m_Shaker->setAmount(10.0f);
	m_Shaker->setWaitTime(0.02f);
	
	/*****************
	***Game Objects***
	*****************/
	m_GameObjects = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();
	m_Player = std::make_shared<Player>("Donald", Vector2f(736.0f, 589.0f));
	m_OL = std::make_shared<ObjectLoader>(m_Player, m_AI, m_GameObjects);

	/*****************
	******Puzzles*****
	*****************/
	m_Puzzles = std::make_shared<vector<std::shared_ptr<Puzzle>>>();
	m_Puzzles->push_back(std::make_shared<LightPuzzle>("light_switch_puzzle", m_GameObjects));
	m_Puzzles->push_back(std::make_shared<NumberPuzzle>("number_puzzle", m_GameObjects));
	m_Puzzles->push_back(std::make_shared<KeyPuzzle>("key_puzzle", m_GameObjects));
	
	/*****************
	*****Managers*****
	*****************/
	m_LM = std::make_shared<LayerManager>(m_GameObjects);
	m_IM = std::make_shared<InteractionManager>(m_GameObjects);
	m_DM = std::make_shared<DialogueManager>(m_AI, m_GameObjects);
	m_Commander = std::make_shared<GameCommander>(m_Player, m_AI, m_OL, m_Puzzles, m_IM, m_Tilemap, m_LM, m_DM, m_GameState, m_ScreenRemote, m_Fader, m_WhiteFader, m_Shaker);
	m_PM = std::make_shared<GamePanelManager>(m_Commander, m_DM, m_Resolution);
	m_InputHandler = std::make_unique<GameInputHandler>(m_PM, m_Commander);
	m_CH = std::make_unique<CollisionHandler>(m_GameObjects, m_Tilemap);
}

Vector2f GameScreen::tilePosition(Vector2f tilePosition) {
	Vector2f actualPosition;
	actualPosition.x = float(tilePosition.x) * 64.0f + (64.0f / 2.0f);
	actualPosition.y = float(tilePosition.y) * 64.0f + (64.0f / 2.0f);
	return actualPosition;
}

void GameScreen::update(float dt) {
	Screen::update(dt); //Panel closes at this line
	
	//Fader
	m_Fader->update(dt);
	m_WhiteFader->update(dt);

	/*****************
	***Game Objects***
	*****************/
	auto it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		if ((*it)->getTag() != "ai") {
			(*it)->update(dt);
		}
	}
	m_AI->update(dt); //A dialogue trigger is made here

	/*****************
	*****Collision****
	*****************/
	m_CH->updateCollisions();

	/*****************
	***Interactions***
	*****************/
	m_Commander->update(dt);

	/*****************
	****GC Updates****
	*****************/
	it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		(*it)->updateGC(dt);
	}

	/*****************
	******Puzzles*****
	*****************/
	auto puzzle = m_Puzzles->begin();
	for (puzzle; puzzle != m_Puzzles->end(); puzzle++) {
		(*puzzle)->update();
	}

	/*****************
	*****Layering*****
	*****************/
	m_LM->updateLayer();

	/*****************
	******Camera******
	*****************/
	m_View.setCenter(Vector2f(round(m_Player->getTC()->getDrawPosition().x), round(m_Player->getTC()->getDrawPosition().y)));
	Listener::setPosition(m_Player->getTC()->getPosition().x, m_Player->getTC()->getPosition().y, 0.0f);
	m_Shaker->update(dt);
}

void GameScreen::initialize() {
	m_GameState->startGame();
	m_AI->prepareForCyberSpace(m_Player, m_Tilemap, m_PM);
	if (!m_GameState->getLightState()) {
		m_Fader->darken();
	}
	m_GameState->travelToCyberspace();
	SoundManager::updateJukeBoxCyberspace(Vector2f(992.0f, 352.0f)); 
}

//Need to draw closer objects first
void GameScreen::draw(RenderWindow& window) {
	window.setView(m_View);
	m_Tilemap->draw(window);
	m_LM->draw(window);

	//DEBUG
	
	auto it = m_GameObjects->begin();
	for (it; it != m_GameObjects->end(); it++) {
		//(*it)->drawTC(window);
	}
	
	std::stringstream temp;
	temp << m_Player->getTC()->getPosition().x << "\n" << m_Player->getTC()->getPosition().y;
	m_Debugger.print(temp.str());
	

	window.setView(m_HUD);
	m_WhiteFader->draw(window);
	m_Fader->draw(window);
	//m_Debugger.draw(window);

	Screen::draw(window);
}

 