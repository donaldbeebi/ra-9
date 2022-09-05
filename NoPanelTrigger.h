#pragma once
#include "PanelManager.h"
#include "Trigger.h"

class NoPanelTrigger : public Trigger {
private:
	std::shared_ptr<PanelManager> m_PanelManager;

public:
	NoPanelTrigger(std::shared_ptr<PanelManager> PM) {
		m_PanelManager = PM;
	}

	virtual void update() {
		if (m_Active) {
			if(m_PanelManager->hasNoOpenPanels()){
				m_Triggered = true;
				m_Active = false;
			}
		}
	}

};