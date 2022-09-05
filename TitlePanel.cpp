#include "TitlePanel.h"

TitlePanel::TitlePanel(Vector2f resolution) : Panel("default", resolution / 2.0f, resolution){
	/************
	***Buttons***
	************/
	m_Buttons = std::make_shared<std::vector<std::shared_ptr<Button>>>();
	m_HasButtons = true;

	m_Buttons->push_back(std::make_shared<Button>("play", "none", "play", Vector2f(200.0f, 324.0f)));
	m_Buttons->push_back(std::make_shared<Button>("exit", "none", "exit", Vector2f(200.0f, 480.0f)));


	/************
	***Selector**
	************/
	m_Selector = std::make_shared<Selector>(m_Buttons);
	m_HasSelector = true;
}


void TitlePanel::actSelector(std::string action) {
	if (action != "none") {
		m_Action = action;
	}
}