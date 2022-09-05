#pragma once
#include "GameState.h"

class Trigger {
protected:
	bool m_Active;
	bool m_Triggered;

public:
	Trigger() { m_Active = false; m_Triggered = false; }
	void activate() { m_Active = true; }
	bool isTriggered() { return m_Triggered; }
	virtual void update() = 0;
};
