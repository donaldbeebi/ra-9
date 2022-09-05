#include "ScreenShaker.h"

ScreenShaker::ScreenShaker(View& view) : Shaker(view) {
	m_CurrentShakeAmount = 0.0f;
	m_ScreenOriginalPosition = m_View.getCenter();
}

void ScreenShaker::stop() {
	m_Triggered = false;
	m_CurrentShakeAmount = 0.0f;
	m_Direction = -1;
	m_View.setCenter(m_ScreenOriginalPosition);
}

void ScreenShaker::update(float dt) {
	if (m_Triggered) {
		m_View.move(Vector2f(0.0f, m_Direction * m_ShakeAmount * dt));
		m_CurrentShakeAmount += m_Direction * m_ShakeAmount * dt;
		if (m_Direction == -1 && m_CurrentShakeAmount < m_ShakeAmount * -1) {
			m_Direction = 1;
		}
		else if (m_Direction == 1 && m_CurrentShakeAmount > m_ShakeAmount * 1) {
			m_Direction = -1;
		}
		std::cout << "shaking" << std::endl;
	}
}