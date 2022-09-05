#include "ScreenRemote.h"

void ScreenRemote::switchScreen(std::string targetScreen) {
	m_TargetScreen = targetScreen;
}

void ScreenRemote::exitGame() {
	m_TargetScreen = "exit";
}

std::string ScreenRemote::getAction() {
	if (m_TargetScreen != "none") {
		std::string temp = m_TargetScreen;
		m_TargetScreen = "none";
		return temp;
	}
	return m_TargetScreen;
}