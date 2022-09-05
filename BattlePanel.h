#pragma once
#include "Panel.h"

class BattlePanel : public Panel {
public:
	BattlePanel(Vector2f resolution);

	virtual void actSelector(std::string action) override;
	virtual void actDialogue(std::string action) override;
};