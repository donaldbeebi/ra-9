#pragma once
#include "Panel.h"

class TitlePanel : public Panel {
public:
	TitlePanel(Vector2f resolution);
	
	virtual void actSelector(std::string) override;
};