#include "DialoguePanel.h"

void DialoguePanel::updatePortrait() {
	if (m_CurrentSpeaker == "RA 9") {
		m_Portrait->show();
		(*m_Buttons)[0]->setPosition(Vector2f(1170.0f, 180.0f));
		m_Selector->setCursor();
	}
	else { 
		m_Portrait->hide();
		(*m_Buttons)[0]->setPosition(Vector2f(1370.0f, 180.0f)); 
		m_Selector->setCursor();
	}
}

DialoguePanel::DialoguePanel(Vector2f resolution) 
	: Panel("dialogue", Vector2f(resolution.x / 2.0f, resolution.y * 0.8), resolution) {

	m_CurrentSpeaker = "none";
	m_CurrentPortraitState = 0;

	/************
	***Buttons***
	************/
	m_Buttons = std::make_shared<std::vector<std::shared_ptr<Button>>>();
	m_HasButtons = true;
	
	std::vector<int> temp;

	m_Buttons->push_back(std::make_shared<Button>("dialogue_next", "none", "dialogue_next", Vector2f(1370.0f, 180.0f)));
	temp.push_back(0);
	m_ButtonGroups.push_back(temp);
	temp.clear();

	m_Buttons->push_back(std::make_shared<Button>("button_A", "none", "true", Vector2f(68.0f, 119.0f)));
	m_Buttons->push_back(std::make_shared<Button>("button_B", "none", "false", Vector2f(68.0f, 176.0f)));
	(*m_Buttons)[1]->hide();
	(*m_Buttons)[2]->hide();
	temp.push_back(1);
	temp.push_back(2);
	m_ButtonGroups.push_back(temp);
	temp.clear();
	

	/************
	***Selector**
	************/
	m_Selector = std::make_shared<Selector>(m_Buttons);
	m_HasSelector = true;

	/************
	***Dialogue**
	************/
	m_DialogueBox = std::make_shared<DialogueBox>("dialogue", Vector2f(720.0f, 120.0f));
	m_DialogueBox->enablePortrait();
	m_HasDialogueBox = true;

	/************
	***Portrait**
	************/
	m_Portrait = std::make_shared<Portrait>(Vector2f(1220, 20));
	m_HasPortrait = true;

	//m_IsReady = false;
}

void DialoguePanel::actSelector(std::string action) {
	if (m_AwaitingMenuResponse && !m_DialogueBox->isPrinting()) {
		if (action != "none") {
			m_Action = m_Command + "_" + action;
			m_Command = "none";
			m_AwaitingMenuResponse = false;
		}
	}
	else {
		if (action == "dialogue_next") {
			if (!m_DialogueBox->isPrinting()) {
				m_Action = "get_dialogue_line";
			}
			else m_DialogueBox->skip();
		}
	}
}

void DialoguePanel::actDialogue(std::string action) {
	if (action == "dialogue_end") {
		m_Action = "close_panel";
	}
	else if (action == "get_dialogue_line") {
		m_Action = "get_dialogue_line";
		m_Ready = false;
	}
	else if (action == "get_interact_command_line") {
		m_Action = "get_interact_command_line";
		m_Ready = false;
	}
	else if (action == "get_standard_command_line") {
		m_Action = "get_standard_command_line";
		m_Ready = false;
	}
	else if (action == "interact_menu_ready_1") {
		switchButtonGroup(1);
	}
}

void DialoguePanel::update(float dt) {
	//Handling the portrait
	std::string speaker = m_DialogueBox->getCurrentSpeaker();
	if (m_CurrentSpeaker != speaker || !m_Portrait->isShowing()) {
		m_CurrentSpeaker = speaker;
		updatePortrait();
	}
	int state = m_DialogueBox->getPortraitState();
	if (m_CurrentPortraitState != state) {
		m_CurrentPortraitState = state;
		m_Portrait->setPortrait(state);
	}
	Panel::update(dt);
}

//bool DialoguePanel::isReady() {
//	return m_IsReady;
//}