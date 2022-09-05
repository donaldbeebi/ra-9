#pragma once
#include "PanelManager.h"
#include "DialoguePanel.h"
#include "DialogueManager.h"

class GamePanelManager : public PanelManager {
private:
	std::shared_ptr<DialogueManager> m_DM;

public:
	GamePanelManager(std::shared_ptr<Commander> commander, std::shared_ptr<DialogueManager> DM, Vector2f resolution);

	virtual void update(float dt) override;

	virtual void actCommander(std::string action) override;
	virtual void actPanel(std::string action) override;
	void checkForDialogue();

	virtual void closeDialogue() {};
};