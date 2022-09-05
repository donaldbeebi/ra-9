#include "PingpongAnimationComponent.h"

PAnimationComponent::PAnimationComponent(std::string texture, Vector2u imageCount) : AnimationComponent(texture, imageCount) {
	m_IsStopped = true;
	m_Forward = false;
	m_State = 0;
}

int PAnimationComponent::getState() {
	return m_State;
}

bool PAnimationComponent::isForward() {
	return m_Forward;
}

bool PAnimationComponent::isPlaying() {
	return !m_IsStopped;
}

void PAnimationComponent::play() {
	m_Forward = true;
	m_IsStopped = false;
}

void PAnimationComponent::reverse() {
	m_Forward = false;
	m_IsStopped = false;
}

void PAnimationComponent::update(float dt) {
	if (!m_IsStopped) {
		m_TotalTime += dt;
		if (m_TotalTime >= m_CurrentSwitchTime) {
			m_TotalTime -= m_CurrentSwitchTime;
			if (m_Forward) {
				if (m_CurrentImage.x == m_ImageCount.x - 1) {
					m_IsStopped = true;
					m_State = 1;
				}
				else {
					m_CurrentImage.x++;
				}
			}
			else {
				if (m_CurrentImage.x == 0) {
					m_IsStopped = true;
					m_State = 0;
				}
				else {
					m_CurrentImage.x--;
				}
			}
		}

		if (m_HasVariedSwitchTimes) {
			m_CurrentSwitchTime = (*m_VariedSwitchTimes)[m_CurrentImage.x];
		}

		m_TextRect.left = m_CurrentImage.x * m_TextRect.width;
		m_TextRect.top = m_CurrentImage.y * m_TextRect.height;
	}
}