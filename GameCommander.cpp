#include "GameCommander.h"

std::shared_ptr<GameObject> GameCommander::findObject(std::string name) {
	for (auto it = m_GameObjects->begin(); it != m_GameObjects->end(); it++) {
		if ((*it)->getName() == name) return (*it);
	}
	return nullptr;
}

std::shared_ptr<Puzzle> GameCommander::findPuzzle(std::string name) {
	for (auto it = m_Puzzles->begin(); it != m_Puzzles->end(); it++) {
		if ((*it)->getName() == name) {
			return (*it);
		}
	}
	return nullptr;
}

GameCommander::GameCommander (std::shared_ptr<Player> player, std::shared_ptr<AI> ai, std::shared_ptr<ObjectLoader> OL,
	std::shared_ptr<std::vector<std::shared_ptr<Puzzle>>> puzzles,
	std::shared_ptr<InteractionManager> IM, std::shared_ptr<Tilemap> tilemap, std::shared_ptr<LayerManager> LM,
	std::shared_ptr<DialogueManager> DM, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, 
	std::shared_ptr<Fader> fader, std::shared_ptr<Fader> whiteFader, std::shared_ptr<Shaker> shaker) 
	: Commander(gameState, screenRemote) {
	m_Player = player;
	m_AI = ai;
	m_OL = OL;
	m_GameObjects = m_OL->getGameObjects();
	m_Puzzles = puzzles;
	m_IM = IM;
	m_Tilemap = tilemap;
	m_LM = LM;
	m_DM = DM;
	m_Fader = fader;
	m_WhiteFader = whiteFader;
	m_Shaker = shaker;
	m_SAIS = std::make_shared<SaveAISequence>(m_Fader, m_WhiteFader, m_ScreenRemote, m_GameState, m_Shaker);
	m_CurrentObjectIndex = 0;
	m_AttemptingInteraction = false;
	m_Interacting = false;
	m_Interacted = false;
	m_CurrentObject = nullptr;
	m_InteractionDisabled = false;

	m_ChangingLevel = false;
	m_LevelToChange = "";
	m_CurrentAction = "none";
}

/********************************
********* INTERACTIONS **********
********************************/

void GameCommander::changeLevel(std::string targetLevel) {
	m_ChangingLevel = true;
	m_LevelToChange = targetLevel;
}

void GameCommander::preparePuzzles() {
	//disable all the puzzles first
	auto it = m_Puzzles->begin();
	for (it; it != m_Puzzles->end(); it++) {
		(*it)->disable();
	}

	if (m_LevelToChange == "lightbulb_room") {
		findPuzzle("light_switch_puzzle")->enable();
	}
	else if (m_LevelToChange == "password_room") {
		findPuzzle("number_puzzle")->enable();
	}
}

/********************************
******** PLAYER'S INPUT *********
********************************/

void GameCommander::pushInteraction() {
	if (!m_InteractionDisabled) {
		for (int i = 0; i < m_GameObjects->size(); i++) {
			Vector2f distance;
			distance.x = abs(m_Player->getTC()->getPosition().x - (*m_GameObjects)[i]->getTC()->getPosition().x);
			distance.y = abs(m_Player->getTC()->getPosition().y - (*m_GameObjects)[i]->getTC()->getPosition().y);

			//If it is within range and the button interact button is pushed
			if ((*m_GameObjects)[i]->hasDC()) {
				if (distance.x < (*m_GameObjects)[i]->getDC()->getRange() && distance.y < (*m_GameObjects)[i]->getDC()->getRange()) {
					(*m_GameObjects)[i]->getDC()->trigger("inspect");
					m_CurrentObject2 = (*m_GameObjects)[i];
					break;
				}
			}
			else if ((*m_GameObjects)[i]->hasIC()) {
				if (distance.x < (*m_GameObjects)[i]->getIC()->getRange() && distance.y < (*m_GameObjects)[i]->getIC()->getRange()) {
					(*m_GameObjects)[i]->getIC()->interact();
					m_CurrentObject2 = (*m_GameObjects)[i];
					m_Interacting = true;
					break;
				}
			}
		}
	}
}

void GameCommander::releaseInteraction() {
	if (!m_InteractionDisabled) {
		if (m_Interacting) {
			m_CurrentObject2->getIC()->release();
			m_Interacting = false;
		}
	}
}

void GameCommander::movePlayer(Direction direction) {
	m_Player->move(direction);
}

/********************************
******* INTERACTION CHECK *******
********************************/

void GameCommander::checkAI() {
	actAI(m_AI->getAction());
}

void GameCommander::checkGameState() {
	actGameState(m_GameState->getAction());
}

void GameCommander::checkInteractiveObjects() {
	actObject(m_IM->getAction());
}

void GameCommander::checkIfPlayerOutOfInteractionRange() {
	if (m_Interacting) {
		Vector2f distance;
		distance.x = abs(m_Player->getTC()->getPosition().x - m_CurrentObject2->getTC()->getPosition().x);
		distance.y = abs(m_Player->getTC()->getPosition().y - m_CurrentObject2->getTC()->getPosition().y);
		//if the player gets out of range
		if (m_CurrentObject2->hasIC()) {
			if (distance.x > m_CurrentObject2->getIC()->getRange() || distance.y > m_CurrentObject2->getIC()->getRange()) {
				m_CurrentObject2->getIC()->release();
				m_Interacting = false;
			}
		}
	}
}

void GameCommander::checkLevelChange() {
	if (m_ChangingLevel) {
		if (!m_Fader->isActive()) {
			if (!m_Fader->isBlack()) m_Fader->fadeOut();
			else {
				//LIGHT'S OUT, CHANGE THE SCENE
				releaseInteraction();
				m_Tilemap->loadLevel(m_LevelToChange);
				m_OL->loadObjects(m_LevelToChange);
				m_LM->updateDrawableObjects();
				m_Player->getTC()->teleport(m_Tilemap->getSpawnLocation());
				preparePuzzles();
				if (m_LevelToChange == "abandoned_room") m_Fader->fadeIn(200);
				else m_Fader->fadeIn();
				if (m_LevelToChange == "bar") {
					SoundManager::unmuteJukeBox();
				}
				else SoundManager::muteQuicklyJukeBox();
				m_ChangingLevel = false;
				m_LevelToChange = "";
			}
		}
	}
}

/********************************
************* UPDATE ************
********************************/

void GameCommander::update(float dt) {
	//Object Interactions
	checkAI();
	checkInteractiveObjects();
	checkIfPlayerOutOfInteractionRange();

	updateGameState();
	checkGameState();

	checkLevelChange();
	m_SAIS->update(dt);
}

/********************************
*********** FEEDBACK ************
********************************/

std::string GameCommander::getPanelAction() {
	if (m_CurrentAction != "none") {
		std::string temp = m_CurrentAction;
		m_CurrentAction = "none";
		return temp;
	}
	else return "none";
}
