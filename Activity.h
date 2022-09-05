#pragma once
#include <string>
#include <iostream>
#include "Trigger.h"

class Activity {
protected:
	std::string m_Activity;
	Trigger* m_Trigger;

public:
	Activity(Trigger* trigger, std::string activity) {
		m_Trigger = trigger;
		m_Activity = activity;
	}

	virtual void activate() {
		m_Trigger->activate();
	}

	virtual void update() {
		m_Trigger->update();
	}

	virtual std::string getAction() {
		if (m_Trigger->isTriggered()) {
			return m_Activity;
		}
		return "none";
	}
};