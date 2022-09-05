#include "Shaker.h"

Shaker::Shaker(View& view) : m_View(view) {
	m_CurrentTime = 0.0f;
	m_WaitTime = 0.05f;
	m_ShakeAmount = 60.0f;
	m_CurrentShakeAmount = m_ShakeAmount;
	m_ShakeReductionAmount = 5.0f;
	m_Stage = 0;
	m_Triggered = false;
	m_Direction = -1;
	m_Started = false;
}

void Shaker::setAmount(float amount) {
	m_ShakeAmount = amount;
	m_CurrentShakeAmount = amount;
}

void Shaker::setWaitTime(float waitTime) {
	m_WaitTime = waitTime;
}

void Shaker::trigger() {
	m_Triggered = true;
	m_Started = false;
}

void Shaker::start() {
	m_Started = true;
	m_Triggered = true;
}

void Shaker::stop() {
	m_Started = false;
	m_Triggered = false;
	m_Stage = 0;
	m_CurrentShakeAmount = m_ShakeAmount;
	m_Direction = -1;
}

void Shaker::update(float dt) {
	if (m_Triggered) {
		if (m_CurrentShakeAmount > 0.0f) {
			switch (m_Stage) {
			case 0:
				m_View.move(Vector2f(0.0f, m_CurrentShakeAmount * m_Direction));
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
				m_View.move(Vector2f(0.0f, m_CurrentShakeAmount * -m_Direction));
				if(!m_Started) m_CurrentShakeAmount -= m_ShakeReductionAmount;
				m_Direction *= -1;
				m_Stage = 0;
			}
		}
		else {
			m_Stage = 0;
			m_CurrentShakeAmount = m_ShakeAmount;
			m_Direction = -1;
			m_Triggered = false;
		}

	}
}