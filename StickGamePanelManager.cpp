#include "StickGamePanelManager.h"

StickGamePanelManager::StickGamePanelManager(std::shared_ptr<Commander> commander, Vector2f resolution) 
	: PanelManager(commander, resolution) {
	(*m_Panels)["stickgame"] = std::make_shared<StickGamePanel>(m_Resolution);
}

void StickGamePanelManager::actCommander(std::string action) {

}

void StickGamePanelManager::actPanel(std::string action) {
	if (action == "get_dialogue_line") {
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_Commander->getDialogueLine());
	}
	else if (action == "get_interact_command_line") {
		//prepare the panel to send the response to the command back
		(*m_Panels)[m_PanelsOpened.back()]->setCommand(m_Commander->getDialogueLine().line);
		//display the line that makes up the interaction menu
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_Commander->getDialogueLine());
	}
	else if (action == "get_another_interact_command_line") {
		//prepare the panel to send the response to the command back
		(*m_Panels)[m_PanelsOpened.back()]->setCommand(m_Commander->getDialogueLine().line);
		//display the line that makes up the interaction menu
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_Commander->getDialogueLine());
	}
	else if (action == "get_standard_command_line") {
		std::string temp = m_Commander->getDialogueLine().line;
		//end the dialogue / play whatever follows
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_Commander->getDialogueLine());
		//then act the command line
		m_Commander->actPanel(temp);
	}
	else if (action == "close_panel") {
		closeCurrentPanel();
	}
	else if (action.find("command") != std::string::npos) {
		//this is a command, act it
		m_Commander->actPanel(action);
		//end the dialogue / play whatever follows
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_Commander->getDialogueLine());
	}
}

void StickGamePanelManager::checkForDialogue() {
	if ((*m_Panels)["stickgame"]->isHidden()) {
		DialogueLine temp = m_Commander->getDialogueLine();
		if (temp.line != "none") {
			openPanel("stickgame");
			(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(temp);
		}
	}
}

void StickGamePanelManager::update(float dt) {
	PanelManager::update(dt);
	checkForDialogue();
}