#include "PanelManager.h"

PanelManager::PanelManager(std::shared_ptr<Commander> commander, Vector2f resolution) {
	m_Commander = commander;
	m_Resolution = resolution;
	m_Panels = std::make_shared<std::map<std::string, std::shared_ptr<Panel>>>();
}

void PanelManager::openPanel(std::string targetPanel) {
	if (m_Panels->find(targetPanel) != m_Panels->end()) {
		(*m_Panels)[targetPanel]->show();
		m_PanelsOpened.push_back(targetPanel);
	}
}

void PanelManager::switchPanel(std::string targetPanel) {
	if (m_Panels->find(targetPanel) != m_Panels->end()) {
		(*m_Panels)[m_PanelsOpened.back()]->hide();
		m_PanelsOpened.push_back(targetPanel);
		(*m_Panels)[m_PanelsOpened.back()]->show();
	}
}

void PanelManager::closeCurrentPanel() {
	if (!m_PanelsOpened.empty()) {
		(*m_Panels)[m_PanelsOpened.back()]->close();
		if ((*m_Panels)[m_PanelsOpened.back()]->hasDialogueBox()) {
			//closeDialogue();
		}
		m_PanelsOpened.pop_back();
		if (!m_PanelsOpened.empty()) {
			(*m_Panels)[m_PanelsOpened.back()]->show();
		}
	}
}

std::shared_ptr<Panel> PanelManager::getCurrentPanel() {
	if (!m_PanelsOpened.empty()) {
		return (*m_Panels)[m_PanelsOpened.back()];
	}
	else return nullptr;
}

bool PanelManager::hasNoOpenPanels() {
	return m_PanelsOpened.empty();
}

void PanelManager::update(float dt) {
	//updating panels
	if (!m_PanelsOpened.empty()) {
		auto it = m_PanelsOpened.begin();
		for (it; it != m_PanelsOpened.end(); it++) {
			(*m_Panels)[(*it)]->update(dt);
		}
	}

	actCommander(m_Commander->getPanelAction());
	if (!m_PanelsOpened.empty()) actPanel((*m_Panels)[m_PanelsOpened.back()]->getAction()); //Panel closes at this line
}

void PanelManager::draw(RenderWindow& window) {
	if (!m_PanelsOpened.empty()) {
		auto it = m_PanelsOpened.begin();
		for (it; it != m_PanelsOpened.end(); it++) {
			(*m_Panels)[(*it)]->draw(window);
		}
	}
}