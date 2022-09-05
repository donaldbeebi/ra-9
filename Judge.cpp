#include "Judge.h"

Judge::Judge(std::shared_ptr<AI> AI) 
	: m_DC("Judge", 0, false) {
	m_DC.disableAutoSection();
	m_GameStarted = false;
	m_Stage = stage::intro;
	m_Waiting = false;
	m_Action = "";
	m_AI = AI;
	m_Section = 0;
	m_AIAttackSequence = 0;
	m_CurrentTime = 0.0f;
}

void Judge::startGame() {
	m_GameStarted = true;
	m_Stage = stage::intro;
	m_Waiting = false;
	m_AIAttackSequence = 0;
}

void Judge::act(int button) {
	m_Waiting = false;
	if (m_Stage == stage::intro) {
		m_Stage = stage::menu;
	}
	else if (m_Stage == stage::menu) {
		switch (button) {
		case 0:
			m_Stage = stage::fight;
			break;
		case 1:
			m_Stage = stage::item;
			break;
		}
	}
	else if (m_Stage == stage::fight) {
		switch (button) {
		case 0:
			if (m_BG.killAI()) {
				m_Section = 3;
			}
			else m_Section = 2;
			break;

		case 1:
			m_Section = 4;
			break;

		case 2:
			m_Section = 5;
			m_BG.lowerDefense();
			break;

		case 3:
			m_Section = 6;
			break;
		}
		m_Stage = stage::fightreport;
	}
	else if (m_Stage == stage::fightreport) {
		m_Stage = stage::healthreport;
	}
	else if (m_Stage == stage::healthreport) {
		if (m_BG.gameEnded()) {
			m_Stage = stage::end;
		}
		else if (!m_BG.isPlayerTurn()) {
			m_Stage = stage::AI;
		}
		else m_Stage = stage::menu;
	}
	else if (m_Stage == stage::item) {
		bool temp = m_BG.useItem(button);
		switch (button) {
		case 0:	
			m_Section = 8;
			break;

		case 1:
			if (temp) m_Section = 9;
			else m_Section = 12;
			break;

		case 2:
			if (temp) m_Section = 10;
			else m_Section = 13;
			break;

		case 3:
			if (temp) m_Section = 11;
			else m_Section = 14;
			break;
		}
		m_Stage = stage::itemreport;
	}
	else if (m_Stage == stage::itemreport) {
		m_Stage = stage::menu;
	}
	else if (m_Stage == stage::AI) {
		m_Stage = stage::AIreport;
	}
	else if (m_Stage == stage::AIreport) {
		m_Stage = stage::healthreport;
	}
	else if (m_Stage == stage::end) {
		//if (m_BG.playerWin()) {
		//	m_Clock.restart();
		//	m_Stage = stage::kill;
		//}
		//else m_Waiting = true; //stop showing the panel
		m_Waiting = true; //stop showing the panel
	}
	else if (m_Stage == stage::kill) {
		m_Waiting = true;
	}
}

void Judge::update() {
	if (m_GameStarted && !m_Waiting) {
		if (m_Stage == stage::intro) {
			m_DC.setSection(23);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::menu) {
			m_DC.setSection(0);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::fight) {
			m_DC.setSection(1);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::fightreport) {
			m_DC.setSection(m_Section);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::healthreport) {
			int temp;
			if (m_BG.isPlayerTurn()) {
				m_DC.setSection(25);
				temp = m_BG.AIHealth();
			}
			else {
				m_DC.setSection(24);
				temp = m_BG.playerHealth();
				if (temp <= 0) 	SoundManager::stopBossTrack();
			}
			m_DC.triggerInput(temp);
			m_Waiting = true;
			m_BG.endTurn();
		}
		else if (m_Stage == stage::item) {
			m_DC.setSection(7);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::itemreport) {
			m_DC.setSection(m_Section);
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::AI) {
			m_DC.setSection(15 + m_AIAttackSequence);
			m_AIAttackSequence++;
			m_AIAttackSequence %= 4;
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::AIreport) {
			m_DC.setSection(19);
			m_DC.triggerInput(m_BG.attackPlayer());
			m_Waiting = true;
		}
		else if (m_Stage == stage::end) {
			if (m_BG.playerWin()) {
				m_DC.setSection(21);
			}
			else {
				m_DC.setSection(20);
			}
			m_DC.trigger("inspect");
			m_Waiting = true;
		}
		else if (m_Stage == stage::kill) {
			m_DC.setSection(22);
			//m_CurrentTime += m_Clock.restart().asSeconds();
			//if (m_CurrentTime > 3.0f) {
				m_DC.trigger("inspect");
				m_Waiting = true;
			//}
		}
	}
}

DialogueLine Judge::getDialogueLine() {
	DialogueLine temp = m_DC.getDialogueLine();
	if (temp.line != "none") {
		return temp;
	}
	return DialogueLine("none", "none");
}

void Judge::triggerStage(stage stage) {
	m_Stage = stage;
	m_Waiting = false;
}

void Judge::returnToMainMenu() {
	if (m_Waiting) {
		if (m_Stage == stage::fight || m_Stage == stage::item) {
			m_Stage = stage::menu;
			m_DC.resetCurrentSection();
			m_DC.setSection(0);
			m_DC.trigger("inspect");
			m_Waiting = true;	
		}
	}
}

stage Judge::getCurrentStage() {
	return m_Stage;
}