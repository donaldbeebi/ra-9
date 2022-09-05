#include "TitlePanelManager.h"

TitlePanelManager::TitlePanelManager(std::shared_ptr<Commander> commander, Vector2f resolution)
	: PanelManager(commander, resolution) {
	(*m_Panels)["title"] = std::make_shared<TitlePanel>(m_Resolution);
	(*m_Panels)["dialogue"] = std::make_shared<DialoguePanel>(m_Resolution);
}

void TitlePanelManager::actCommander(std::string action) {

}

void TitlePanelManager::actPanel(std::string action) {
	if (action == "play") {
		m_Commander->actPanel(action);
	}
	else if (action == "exit") {
		m_Commander->actPanel(action);
	}
	else if (action == "get_dialogue_line") {
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

void TitlePanelManager::checkForDialogue() {
	if ((*m_Panels)["dialogue"]->isHidden()) {
		DialogueLine temp = m_Commander->getDialogueLine();
		if (temp.line != "none") {
			openPanel("dialogue");
			(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(temp);
		}
	}
}

void TitlePanelManager::update(float dt) {
	PanelManager::update(dt); //Panel closes at this line
	checkForDialogue();
}