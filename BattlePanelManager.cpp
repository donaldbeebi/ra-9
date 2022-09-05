#include "BattlePanelManager.h"

BattlePanelManager::BattlePanelManager(std::shared_ptr<Commander> commander, Vector2f resolution)
	: PanelManager(commander, resolution) {
	(*m_Panels)["battle"] = std::make_shared<BattlePanel>(m_Resolution);
}

void BattlePanelManager::actCommander(std::string action) {

}

void BattlePanelManager::actPanel(std::string action) {
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
		if (temp == "command_shake") {
			if ((*m_Panels)[m_PanelsOpened.back()]->hasShaker()) {
				(*m_Panels)[m_PanelsOpened.back()]->getShaker()->trigger();
				SoundManager::play("hitplayer");
			}
			m_Commander->actPanel("command_next");
		}
		else m_Commander->actPanel(temp);
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

void BattlePanelManager::checkForDialogue() {
	if ((*m_Panels)["battle"]->isHidden()) {
		DialogueLine temp = m_Commander->getDialogueLine();
		if (temp.line != "none") {
			openPanel("battle");
			(*m_Panels)[m_PanelsOpened.back()]->getDialogueBox()->play(temp);
		}
	}
}

void BattlePanelManager::update(float dt) {
	PanelManager::update(dt);
	checkForDialogue();
}

void BattlePanelManager::closeDialogue() {
}