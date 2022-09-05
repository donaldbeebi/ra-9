#include "TremblingComponent.h"

TremblingComponent::TremblingComponent(std::shared_ptr<TransformComponent> TC) {
	m_TC = TC;
	m_CurrentTime = 0.0f;
	m_WaitTime = 0.05f;
	m_Triggered = false;
	m_Movement = 60.0f;
	m_CurrentMovement = m_Movement;
	m_Reduction = 3.0f;
	m_Direction = -1;
	m_Stage = 0;
}

void TremblingComponent::trigger() {
	m_Triggered = true;
	m_Reduction = 3.0f;
	m_WaitTime = 0.08f;
}

void TremblingComponent::triggerBig() {
	m_Triggered = true;
	m_CurrentMovement = 100.0f;
	m_Reduction = 5.0f;
	m_WaitTime = 0.1f;
}

void TremblingComponent::update(float dt) {
	if (m_Triggered) {
		if (m_CurrentMovement > 0.0f) {
			switch (m_Stage) {
			case 0:
				m_TC->move(Vector2f(m_CurrentMovement * m_Direction, 0.0f));
				m_Stage++;
				break;
			case 1:
				m_CurrentTime += dt;
				if (m_CurrentTime > m_WaitTime) {
					m_CurrentTime = 0.0f;
					m_Stage++;
				}
				break;
			case 2:
				m_TC->move(Vector2f(m_CurrentMovement * (-m_Direction), 0.0f));
				m_Stage = 0;
				m_CurrentMovement -= m_Reduction;
				m_Direction = -m_Direction;
				break;
			}
		}
		else {
			m_CurrentMovement = m_Movement;
			m_Direction = -1;
			m_Triggered = false;
		}
	}
}