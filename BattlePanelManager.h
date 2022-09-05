#pragma once
#include "PanelManager.h"
#include "BattlePanel.h"

class BattlePanelManager : public PanelManager {
public:
	BattlePanelManager(std::shared_ptr<Commander> commander, Vector2f resolution);
	
	virtual void actCommander(std::string action) override;	//from commander to PM
	virtual void actPanel(std::string action) override;	//from Panels
	void checkForDialogue();

	virtual void update(float dt);
	virtual void closeDialogue() override;
};