#pragma once
#include <memory>
#include <list>
#include <map>
#include "Panel.h"
#include "Commander.h"

typedef std::shared_ptr<std::map<std::string, std::shared_ptr<Panel>>> Panel_Map;

class PanelManager {
protected:
	Panel_Map m_Panels;
	std::list<std::string> m_PanelsOpened;
	std::shared_ptr<Commander> m_Commander;
	Vector2f m_Resolution;

public:
	PanelManager(std::shared_ptr<Commander> commander, Vector2f resolution);

	void openPanel(std::string targetPanel);
	void switchPanel(std::string targetPanel);
	void closeCurrentPanel();

	//for input handler
	std::shared_ptr<Panel> getCurrentPanel();
	bool hasNoOpenPanels();

	virtual void actCommander(std::string action) = 0;
	virtual void actPanel(std::string action) = 0;

	virtual void update(float dt);
	void draw(RenderWindow& window);

	virtual void closeDialogue() = 0;
};