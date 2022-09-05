#pragma once
#include "Trigger.h"

class ImmediateTrigger : public Trigger {
public:
	virtual void update() {
		if (m_Active) {
			m_Triggered = true;
			m_Active = false;
		}
	}
};