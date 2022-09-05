#include "LoopedAnimationComponent.h"

LAnimationComponent::LAnimationComponent(std::string texture, Vector2u imageCount) : AnimationComponent(texture, imageCount) {}

void LAnimationComponent::update(float dt){
	if (!m_IsStopped) {
		m_TotalTime += dt;
		if (m_TotalTime >= m_CurrentSwitchTime) {
			m_TotalTime -= m_CurrentSwitchTime;
			m_CurrentImage.x++;
			if (m_CurrentImage.x == m_ImageCount.x) {
				m_CurrentImage.x = 0;
			}

			if (m_HasVariedSwitchTimes) {
				m_CurrentSwitchTime = (*m_VariedSwitchTimes)[m_CurrentImage.x];
			}
		}
		m_TextRect.left = m_CurrentImage.x * m_TextRect.width;
		m_TextRect.top = m_CurrentImage.y * m_TextRect.height;
	}
}