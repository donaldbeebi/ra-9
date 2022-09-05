#pragma once
#include "PanelManager.h"
#include "StickGamePanel.h"

class StickGamePanelManager : public PanelManager {
public:
	StickGamePanelManager(std::shared_ptr<Commander> commander, Vector2f resolution);

	virtual void actCommander(std::string action) override; //from Commander to PM
	virtual void actPanel(std::string action) override; //from Panel
	void checkForDialogue();

	virtual void update(float dt);

	virtual void closeDialogue() {};
};