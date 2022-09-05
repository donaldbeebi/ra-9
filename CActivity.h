#pragma once
#include "Activity.h"

class CActivity : public Activity {
private:
	std::string m_CActivity;
	Trigger* m_CTrigger;

public:
	CActivity(Trigger* trigger, std::string activity, Trigger* ctrigger, std::string cactivity) 
		: Activity(trigger, activity) {
		m_CTrigger = ctrigger;
		m_CActivity = cactivity;
	}

	virtual void activate() override {
		m_Trigger->activate();
		m_CTrigger->activate();
	}

	virtual void update() override {
		m_Trigger->update();
		m_CTrigger->update();
	}

	virtual std::string getAction() override {
		if (m_Trigger->isTriggered()) {
			return m_Activity;
		}
		if (m_CTrigger->isTriggered()) {
			return m_CActivity;
		}
		return "none";
	}
};