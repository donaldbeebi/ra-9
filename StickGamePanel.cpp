#include "StickGamePanel.h"

StickGamePanel::StickGamePanel(Vector2f resolution) 
	: Panel("stickgame", Vector2f(resolution.x / 2.0f, resolution.y * 0.82), resolution) {
	
	/************
	***Buttons***
	************/
	m_Buttons = std::make_shared<std::vector<std::shared_ptr<Button>>>();
	m_HasButtons = true;

	std::vector<int> temp;

	m_Buttons->push_back(std::make_shared<Button>("dialogue_next", "none", "dialogue_next", Vector2f(1370.0f, 300.0f)));
	temp.push_back(0);
	m_ButtonGroups.push_back(temp);
	temp.clear();

	m_Buttons->push_back(std::make_shared<Button>("button_A", "none", "0", Vector2f(68.0f, 119.0f)));
	m_Buttons->push_back(std::make_shared<Button>("button_B", "none", "1", Vector2f(68.0f, 176.0f)));
	(*m_Buttons)[1]->hide();
	(*m_Buttons)[2]->hide();
	temp.push_back(1);
	temp.push_back(2);
	m_ButtonGroups.push_back(temp);
	temp.clear();

	m_Buttons->push_back(std::make_shared<Button>("button_1", "none", "0", Vector2f(68.0f, 119.0f)));
	m_Buttons->push_back(std::make_shared<Button>("button_2", "none", "1", Vector2f(68.0f, 176.0f)));
	m_Buttons->push_back(std::make_shared<Button>("button_3", "none", "2", Vector2f(68.0f, 233.0f)));
	m_Buttons->push_back(std::make_shared<Button>("button_4", "none", "3", Vector2f(68.0f, 290.0f)));
	(*m_Buttons)[3]->hide();
	(*m_Buttons)[4]->hide();
	(*m_Buttons)[5]->hide();
	(*m_Buttons)[6]->hide();
	temp.push_back(3);
	temp.push_back(4);
	temp.push_back(5);
	temp.push_back(6);
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
	m_DialogueBox = std::make_shared<DialogueBox>("stickgame", Vector2f(720.0f, 180.0f));
	m_HasDialogueBox = true;
}

void StickGamePanel::actSelector(std::string action) {
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

void StickGamePanel::actDialogue(std::string action) {
	if (action == "dialogue_end") {
		m_Action = "close_panel";
	}
	else if (action == "get_dialogue_line") {
		m_Action = "get_dialogue_line";
	}
	else if (action == "get_interact_command_line") {
		m_Action = "get_interact_command_line";
	}
	else if (action == "get_another_interact_command_line") {
		m_Action = "get_another_interact_command_line";
	}
	else if (action == "get_standard_command_line") {
		m_Action = "get_standard_command_line";
	}
	else if (action == "switch_button_group_0") {
		switchButtonGroup(0);
	}
	else if (action == "interact_menu_ready_1") {
		switchButtonGroup(1);
	}
	else if (action == "interact_menu_ready_2") {
		switchButtonGroup(2);
	}
}