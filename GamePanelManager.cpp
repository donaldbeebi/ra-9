#include "GamePanelManager.h"

GamePanelManager::GamePanelManager(std::shared_ptr<Commander> commander, std::shared_ptr<DialogueManager> DM, Vector2f resolution)
	: PanelManager(commander, resolution) {
	m_DM = DM;
	(*m_Panels)["dialogue"] = std::make_shared<DialoguePanel>(m_Resolution);
}

void GamePanelManager::update(float dt) {
	PanelManager::update(dt); //Panel closes at this line
	checkForDialogue();
}

void GamePanelManager::actCommander(std::string action) {

}

void GamePanelManager::actPanel(std::string action) {
	if (action == "get_dialogue_line") {
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_DM->getDialogueLine());
	}
	else if (action == "get_interact_command_line") {
		//prepare the panel to send the response to the command back
		(*m_Panels)[m_PanelsOpened.back()]->setCommand(m_DM->getDialogueLine().line);
		//display the line that makes up the interaction menu
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_DM->getDialogueLine());
	}
	else if (action == "get_standard_command_line") {
		std::string temp = m_DM->getDialogueLine().line;
		//end the dialogue / play whatever follows
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_DM->getDialogueLine());
		//then act the command line
		m_Commander->actPanel(temp);
	}
	else if (action == "close_panel") {
		closeCurrentPanel();
	}
	else if (action.find("command") != std::string::npos) {
		//end the dialogue / play whatever follows
		(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(m_DM->getDialogueLine());
		//this is a command, act it
		m_Commander->actPanel(action);
	}
}

void GamePanelManager::checkForDialogue() {
	if ((*m_Panels)["dialogue"]->isHidden()) {
		DialogueLine temp = m_DM->getDialogueLine();
		if (temp.line != "none") {
			openPanel("dialogue");
			(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(temp);
		}
	}
}