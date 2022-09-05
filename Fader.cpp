#include "Fader.h"

Fader::Fader(Vector2f screenSize) {
	m_Alpha = 0.0f;
	m_Fader.setSize(screenSize);
	m_Fader.setFillColor(Color(0, 0, 0, int(m_Alpha)));
	m_FadingIn = false;
	m_Active = false;
	m_Black = false;
	m_TargetAlpha = 0;
	m_Rate = 5.0f;
	m_Color = 0;
}

void Fader::setWhite() {
	m_Fader.setFillColor(Color(255, 255, 255, int(m_Alpha)));
	m_Color = 255;
}

void Fader::setTime(float timeInSeconds) {
	m_Rate = 1 / timeInSeconds;
}

void Fader::fadeIn() {
	m_FadingIn = true;
	m_Active = true;
	m_TargetAlpha = 0;
}

void Fader::fadeIn(int alpha) {
	m_FadingIn = true;
	m_Active = true;
	m_TargetAlpha = alpha;
}

void Fader::fadeOut() {
	m_FadingIn = false;
	m_Active = true;
}

void Fader::darken() {
	m_Alpha = 255;
	m_Black = true;
	m_Fader.setFillColor(Color(0, 0, 0, int(m_Alpha)));
}

void Fader::dim() {
	m_Alpha = 100;
	m_Black = true;
	m_Fader.setFillColor(Color(0, 0, 0, int(m_Alpha)));
}

void Fader::brighten() {
	m_Alpha = 0;
	m_Black = false;
	m_Fader.setFillColor(Color(0, 0, 0, int(m_Alpha)));
}

bool Fader::isActive() {
	return m_Active;
}

bool Fader::isBlack() {
	return m_Black;
}

void Fader::update(float dt) {
	if (m_Active) {
		if (m_FadingIn) {
			m_Alpha -= 255 * m_Rate * dt;
			if (m_Alpha <= m_TargetAlpha) {
				m_Alpha = m_TargetAlpha;
				m_Black = false;
				m_Active = false;
			}
		}
		else {
			m_Alpha += 255 * m_Rate * dt;
			if (m_Alpha >= 255) {
				m_Alpha = 255;
				m_Black = true;
				m_Active = false;
			}
		}
		m_Fader.setFillColor(Color(m_Color, m_Color, m_Color, int(m_Alpha)));
	}
}

void Fader::draw(RenderWindow& window) {
	window.draw(m_Fader);
}
