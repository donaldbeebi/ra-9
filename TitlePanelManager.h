#pragma once
#include "ScreenManager.h"
#include "TitlePanel.h"
#include "DialoguePanel.h"

class TitlePanelManager : public PanelManager {
public:
	TitlePanelManager(std::shared_ptr<Commander> commander, Vector2f resolution);

	virtual void actCommander(std::string action) override;
	virtual void actPanel(std::string action) override;

	void checkForDialogue();

	virtual void update(float dt) override;

	virtual void closeDialogue() {};
};