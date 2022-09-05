#pragma once
#include <SFML/Graphics.hpp>
#include "PanelManager.h"
#include "Trigger.h"

using namespace sf;

class TimeTrigger : public Trigger {
private:
	Clock m_Clock;
	bool m_Started;
	float m_TriggerTime;
	float m_CurrentTime;
	std::shared_ptr<PanelManager> m_PanelManager;

public:
	TimeTrigger(float durationInSeconds, std::shared_ptr<PanelManager> PM) {
		m_TriggerTime = durationInSeconds;
		m_PanelManager = PM;
		m_Started = false;
	}

	virtual void update() {
		if (m_Active) {
			if (!m_Started && m_PanelManager->hasNoOpenPanels()) {
				m_Started = true;
				m_Clock.restart();
			}
			if (m_Started) {
				float temp = m_Clock.restart().asSeconds();
				if (m_PanelManager->hasNoOpenPanels()) {
					m_CurrentTime += temp;
				}
			}
			if (m_CurrentTime >= m_TriggerTime) {
				m_Triggered = true;
				m_Active = false;
			}
		}
	}
};