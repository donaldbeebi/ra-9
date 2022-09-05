#include "GameMaster.h"

GameMaster::GameMaster(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects, std::shared_ptr<AI> AI, std::shared_ptr<GameState> gameState) 
	: m_DC("GameMaster", 0, false), m_Chat("GameMaster_Chat", 0, false) {
	m_DC.disableAutoSection();
	m_GameStarted = false;
	m_Phase = phase::menu;
	m_Waiting = false;
	m_Action = "";
	m_ChatSection = 15;
	m_ChatSectionOffset = 8;
	m_ChatOption = 0;
	m_PlayerSaidSomething = false;
	m_IsDark = false;
	srand((int)time(0));
	m_UnwillingToTalk = false;

	m_GameObjects = std::make_shared<std::vector<std::shared_ptr<GameObject>>>();
	for (auto it = gameObjects->begin(); it != gameObjects->end(); it++) {
		if ((*it)->getTag() == "stick") {
			m_GameObjects->push_back(*it);
		}
	}
	m_AI = AI;
	m_GameState = gameState;
}

void GameMaster::startGame() {
	if (!m_GameStarted) m_GameStarted = true;
	else {
		m_SG.restartMatch();
		for (auto it = m_GameObjects->begin(); it != m_GameObjects->end(); it++) {
			(*it)->getGC()->enable();
		}
		m_Phase = phase::menu;
		m_Waiting = false;
		if (m_GameState->AIKilled() || m_GameState->AISpared() || m_GameState->AISaved()) {
			m_ChatSection = 0;
		}
	}
}

void GameMaster::lightIsOn(bool state) {
	m_IsDark = !state;
}

void GameMaster::act(int button) {
	if (m_Phase == phase::menu) {
		switch (button) {
		case 0:
			m_Phase = phase::stick;
			break;
		case 1:
			if (!m_PlayerSaidSomething && !m_UnwillingToTalk) m_Phase = phase::chat;
			else m_Phase = phase::chatCD;
			break;
		case 2:
			m_Phase = phase::other;
			break;
		}
	}
	else if (m_Phase == phase::stick) {
		if (!m_IsDark) {
			m_SG.removeSticks(button + 1);
			if (m_SG.sticksRemoved() > 0) {
				for (int i = m_SG.numberOfSticksLeft(); i != 21; i++) {
					(*m_GameObjects)[i]->getGC()->disable();
				}
				m_SG.endTurn();
				m_Phase = phase::board;
			}
			else m_Phase = phase::bad;
		}
		else {
			int maxSticks = std::min(4, m_SG.numberOfSticksLeft());
			m_SG.removeSticks((rand() % maxSticks) + 1);
			m_SG.endTurn();
			m_Phase = phase::random;
		}
	}
	else if (m_Phase == phase::random) {
		m_Phase = phase::board;
	}
	else if (m_Phase == phase::chat) {
		if (button == 0 || button == 1) {
			if (!m_GameState->AIKilled() && !m_GameState->AISpared() && !m_GameState->AISaved()) {
				calculateChatSection(button);
			}
			m_PlayerSaidSomething = true;
			m_AI->ifPlayerSaid(m_ChatSection);
			//return;
			//closes panel
		}
		m_Phase = phase::menu;
	}
	else if (m_Phase == phase::board) {
		if (m_SG.numberOfSticksLeft() < 1) {
			m_Phase = phase::gameover;
		}
		else {
			if (m_SG.playerTurn()) {
				m_Phase = phase::menu;
			}
			else {
				if (m_GameState->AISaved() || m_GameState->AIKilled() || m_GameState->AISpared()) {
					m_Phase = phase::noAI;
				}
				else {
					m_Phase = phase::AI;
				}
			}
		}
	}
	else if (m_Phase == phase::AI) {
		m_Phase = phase::board;
	}
	else if (m_Phase == phase::noAI) {
		if (m_PlayerSaidSomething && !m_GameState->AISpared()) {
			m_Phase = phase::noresponse;
		}
		else {
			m_Phase = phase::menu;
			m_PlayerSaidSomething = false;
		}
	}
	else if (m_Phase == phase::noresponse) {
		m_Phase = phase::menu;
	}
	else if (m_Phase == phase::bad) {
		m_Phase = phase::stick;
	}
	else if (m_Phase == phase::chatCD) {
		m_Phase = phase::menu;
	}
	else if (m_Phase == phase::gameover) {
		m_Phase = phase::confirm;
	}
	else if (m_Phase == phase::confirm) {
		m_SG.restartMatch();
		for (auto it = m_GameObjects->begin(); it != m_GameObjects->end(); it++) {
			(*it)->getGC()->enable();
		}
		m_Phase = phase::menu;
	}
	else if (m_Phase == phase::other) {
		m_Phase = phase::menu;
	}
	m_Waiting = false;
}

void GameMaster::update() {
	if (m_GameStarted && !m_Waiting) {
		if(m_Phase == phase::menu) {
			m_DC.setSection(0);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Phase == phase::stick) {
			m_DC.setSection(1);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Phase == phase::chat) {
			if (m_ChatSection == 26) m_ChatSection = 23;
			m_Chat.setSection(m_ChatSection);
			m_Chat.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Phase == phase::board) {
			m_DC.setSection(2);
			m_DC.triggerInput(m_SG.numberOfSticksLeft());
			m_Waiting = true;
		}

		else if (m_Phase == phase::bad) {
			m_DC.setSection(3);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Phase == phase::random) {
			m_DC.setSection(10);
			m_DC.triggerInput(m_SG.sticksRemoved());
			m_Waiting = true;
		}
		else if (m_Phase == phase::AI) {
			if (m_PlayerSaidSomething) {
				m_AI->saySomething();
				if (m_ChatSection == 22) SoundManager::muteJukeBox();
				m_PlayerSaidSomething = false;
				m_Waiting = true;
			}
			else {
				int temp = m_AI->removeSticksIfThereAre(m_SG.numberOfSticksLeft());
				m_SG.removeSticks(temp);
				for (int i = m_SG.numberOfSticksLeft(); i != 21; i++) {
					(*m_GameObjects)[i]->getGC()->disable();
				}
				m_DC.setSection(4);
				m_DC.triggerInput(temp);
				m_SG.endTurn();
				m_Waiting = true;
			}
		}
		else if (m_Phase == phase::noAI) {
			if (m_GameState->AISpared()) {
				m_DC.setSection(12);
			}
			else m_DC.setSection(11);
			m_DC.trigger("inspect");
			m_SG.endTurn();
			m_Waiting = true;
		}
		else if (m_Phase == phase::noresponse) {
			m_DC.setSection(15);
			m_DC.trigger("inspect");
			m_Waiting = true;
			m_PlayerSaidSomething = false;
		}
		else if (m_Phase == phase::gameover) {
			if (m_SG.playerWin()) {
				m_DC.setSection(5);
				m_DC.trigger("inspect");
				m_Waiting = true;
			}
			else {
				if (m_GameState->AISaved()) {
					m_DC.setSection(13);
				}
				else if (m_GameState->AIKilled() || m_GameState->AISpared()) {
					m_DC.setSection(14);
				}
				else m_DC.setSection(6);
				m_DC.trigger("inspect");
				m_Waiting = true;
			}
		}
		else if (m_Phase == phase::confirm) {
			m_DC.setSection(7);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Phase == phase::other) {
			m_DC.setSection(8);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Phase == phase::chatCD) {
			if (m_UnwillingToTalk) m_DC.setSection(16);
			else m_DC.setSection(9);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
	}
}

void GameMaster::triggerPhase(phase phase) {
	m_Waiting = false;
	m_Phase = phase;
}

DialogueLine GameMaster::getDialogueLine() {
	DialogueLine temp = m_DC.getDialogueLine();
	if (temp.line != "none") return temp;
	return m_Chat.getDialogueLine();
}

void GameMaster::calculateChatSection(int button) {
	if (!m_UnwillingToTalk) {
		if (m_ChatSection == 0 || (m_ChatSection > 3 && m_ChatSection < 8)) {
			if (m_ChatSection == 0) m_ChatSectionOffset = 1;
			else m_ChatSectionOffset = 8;
		}

		if (m_ChatSection == 0) m_ChatSection = 1;
		else if (m_ChatSection > 3 && m_ChatSection < 8) {
			m_ChatSection = 8;
		}
		else if (m_ChatSection == 23) {
			m_ChatSection = m_ChatSection + 2 + button;
		}
		else {
			m_ChatSection -= m_ChatSectionOffset;
			m_ChatSection = m_ChatSection * 2 + (button + 1);
			m_ChatSection += m_ChatSectionOffset;
		}

		if ((m_ChatSection > 15 && m_ChatSection < 22) || m_ChatSection == 24) {
			m_UnwillingToTalk = true;
		}
	}
}

void GameMaster::returnToMainMenu() {
	if (m_Waiting) {
		if (m_Phase == phase::chat || m_Phase == phase::stick || m_Phase == phase::other) {
			m_Phase = phase::menu;
			m_DC.resetCurrentSection();
			m_DC.setSection(0);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
	}
}

phase GameMaster::getCurrentPhase() {
	return m_Phase;
}