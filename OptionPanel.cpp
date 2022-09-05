#include "OptionPanel.h"

OptionPanel::OptionPanel(Vector2f resolution) 
	: Panel("default", resolution / 2.0f, resolution) {
	
	/************
	***Buttons***
	************/
	m_Buttons = std::make_shared<std::vector<std::shared_ptr<Button>>>();
	m_HasButtons = true;

	m_Buttons->push_back(std::make_shared<Button>("text_speed", "none", "text_speed", Vector2f(200.0f, 160.0f)));
	m_Buttons->push_back(std::make_shared<Button>("return", "none", "return", Vector2f(200.0f, 320.0f)));

	/************
	***Selector**
	************/
	m_Selector = std::make_shared<Selector>(m_Buttons);
	m_HasSelector = true;
}