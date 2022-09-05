#pragma once
#include "Panel.h"

class StickGamePanel : public Panel {
public:
	StickGamePanel(Vector2f resolution);

	virtual void actSelector(std::string action) override;
	virtual void actDialogue(std::string action) override;
};