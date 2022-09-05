#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundBuffer SoundManager::m_BlipB;
Sound SoundManager::m_BlipS;

SoundBuffer SoundManager::m_ClickB;
Sound SoundManager::m_ClickS;
SoundBuffer SoundManager::m_ClockB;
Sound SoundManager::m_ClockS;

SoundBuffer SoundManager::m_SwitchPushB;
Sound SoundManager::m_SwitchPushS;
SoundBuffer SoundManager::m_SwitchReleaseB;
Sound SoundManager::m_SwitchReleaseS;

SoundBuffer SoundManager::m_ButtonPushB;
Sound SoundManager::m_ButtonPushS;
SoundBuffer SoundManager::m_ButtonReleaseB;
Sound SoundManager::m_ButtonReleaseS;

SoundBuffer SoundManager::m_BigButtonPushB;
Sound SoundManager::m_BigButtonPushS;
SoundBuffer SoundManager::m_BigButtonReleaseB;
Sound SoundManager::m_BigButtonReleaseS;

SoundBuffer SoundManager::m_hitAIB;
Sound SoundManager::m_hitAIS;
SoundBuffer SoundManager::m_hitAICriticalB;
Sound SoundManager::m_hitAICriticalS;
SoundBuffer SoundManager::m_hitPlayerB;
Sound SoundManager::m_hitPlayerS;

SoundBuffer SoundManager::m_AlarmB;
Sound SoundManager::m_AlarmS;
SoundBuffer SoundManager::m_RiserB;
Sound SoundManager::m_RiserS;

SoundBuffer SoundManager::m_HealB;
Sound SoundManager::m_HealS;

Music SoundManager::m_Track1;
Music SoundManager::m_BossTrack;

bool SoundManager::m_ChangingJukeBox;
float SoundManager::m_Rate;
float SoundManager::m_CurrentVolume;

SoundManager::SoundManager() {
	m_BlipB.loadFromFile("sounds/blip.wav");
	m_BlipS.setBuffer(m_BlipB);
	m_BlipS.setRelativeToListener(true);
	m_BlipS.setVolume(80);

	m_ClickB.loadFromFile("sounds/click.wav");
	m_ClickS.setBuffer(m_ClickB);
	m_ClickS.setRelativeToListener(true);
	m_ClickS.setVolume(30);

	m_ClockB.loadFromFile("sounds/clock.wav");
	m_ClockS.setBuffer(m_ClockB);
	m_ClockS.setRelativeToListener(true);
	m_ClockS.setVolume(30);

	m_SwitchPushB.loadFromFile("sounds/switchpush.wav");
	m_SwitchPushS.setBuffer(m_SwitchPushB);
	m_SwitchPushS.setVolume(80);
	m_SwitchPushS.setRelativeToListener(true);

	m_SwitchReleaseB.loadFromFile("sounds/switchrelease.wav");
	m_SwitchReleaseS.setBuffer(m_SwitchReleaseB);
	m_SwitchReleaseS.setVolume(60);
	m_SwitchReleaseS.setRelativeToListener(true);

	m_ButtonPushB.loadFromFile("sounds/buttonpush.wav");
	m_ButtonPushS.setBuffer(m_ButtonPushB);
	m_ButtonPushS.setVolume(40);
	m_ButtonPushS.setRelativeToListener(true);

	m_ButtonReleaseB.loadFromFile("sounds/buttonrelease.wav");
	m_ButtonReleaseS.setBuffer(m_ButtonReleaseB);
	m_ButtonReleaseS.setVolume(20);
	m_ButtonReleaseS.setRelativeToListener(true);

	m_BigButtonPushB.loadFromFile("sounds/bigbuttonpush.wav");
	m_BigButtonPushS.setBuffer(m_BigButtonPushB);
	m_BigButtonPushS.setVolume(70);
	m_BigButtonPushS.setRelativeToListener(true);

	m_BigButtonReleaseB.loadFromFile("sounds/bigbuttonrelease.wav");
	m_BigButtonReleaseS.setBuffer(m_BigButtonReleaseB);
	m_BigButtonReleaseS.setVolume(50);
	m_BigButtonReleaseS.setRelativeToListener(true);

	m_hitAIB.loadFromFile("sounds/hitAI.wav");
	m_hitAIS.setBuffer(m_hitAIB);
	m_hitAIS.setRelativeToListener(true);
	m_hitAIS.setVolume(30);

	m_hitAICriticalB.loadFromFile("sounds/hitAIcritical.wav");
	m_hitAICriticalS.setBuffer(m_hitAICriticalB);
	m_hitAICriticalS.setRelativeToListener(true);
	m_hitAICriticalS.setVolume(40);

	m_hitPlayerB.loadFromFile("sounds/hitplayer.wav");
	m_hitPlayerS.setBuffer(m_hitPlayerB);
	m_hitPlayerS.setRelativeToListener(true);
	m_hitPlayerS.setVolume(80);

	m_AlarmB.loadFromFile("sounds/alarm.wav");
	m_AlarmS.setBuffer(m_AlarmB);
	m_AlarmS.setVolume(80);
	m_AlarmS.setRelativeToListener(true);
	m_AlarmS.setLoop(true);

	m_RiserB.loadFromFile("sounds/riser.wav");
	m_RiserS.setBuffer(m_RiserB);
	m_RiserS.setVolume(100);
	m_RiserS.setRelativeToListener(true);

	m_HealB.loadFromFile("sounds/heal.wav");
	m_HealS.setBuffer(m_HealB);
	m_HealS.setRelativeToListener(true);
	m_HealS.setVolume(50);

	m_Track1.openFromFile("sounds/track1.wav");
	m_Track1.setRelativeToListener(true);
	m_Track1.setMinDistance(500);
	m_Track1.setAttenuation(2.0f);
	m_Track1.setVolume(30);
	m_Track1.setLoop(true);

	m_BossTrack.openFromFile("sounds/bosstrack.wav");
	m_BossTrack.setRelativeToListener(true);
	m_BossTrack.setVolume(60);
	m_BossTrack.setLoop(true);

	m_ChangingJukeBox = false;
	m_Rate = 0;
	m_CurrentVolume = m_Track1.getVolume();
}

void SoundManager::play(std::string sound) {
	if (sound == "blip") {
		m_BlipS.play();
	}
	else if (sound == "click") {
		m_ClickS.play();
	}
	else if (sound == "clock") {
		m_ClockS.play();
	}
	else if (sound == "switchpush") {
		m_SwitchPushS.play();
	}
	else if (sound == "switchrelease") {
		m_SwitchReleaseS.play();
	}
	else if (sound == "buttonpush") {
		m_ButtonPushS.play();
	}
	else if (sound == "buttonrelease") {
		m_ButtonReleaseS.play();
	}
	else if (sound == "bigbuttonpush") {
		m_BigButtonPushS.play();
	}
	else if (sound == "bigbuttonrelease") {
		m_BigButtonReleaseS.play();
	}
	else if (sound == "hitAI") {
		m_hitAIS.play();
	}
	else if (sound == "hitAIcritical") {
		m_hitAICriticalS.play();
	}
	else if (sound == "hitplayer") {
		m_hitPlayerS.play();
	}
	else if (sound == "riser") {
		m_RiserS.play();
	}
	else if (sound == "heal") {
		m_HealS.play();
	}
}

void SoundManager::startJukeBox() {
	if (m_Track1.getStatus() != Music::Playing) {
		m_Track1.play();
	}
}

void SoundManager::switchJukeBox() {
	
}

void SoundManager::stopJukeBox() {
	m_Track1.stop();
}

void SoundManager::toggleJukeBox() {
	if (m_Track1.getStatus() == Music::Playing) {
		m_Track1.stop();
	}
	else m_Track1.play();
}

void SoundManager::updateJukeBoxStickGame() {
	m_Track1.setRelativeToListener(true);
	m_Track1.setPosition(0.f, 0.f, 0.f);
}

void SoundManager::updateJukeBoxCyberspace(Vector2f location) {
	m_Track1.setRelativeToListener(false);
	m_Track1.setPosition(location.x, location.y, 0.0f);
}

void SoundManager::muteJukeBox() {
	m_ChangingJukeBox = true;
	m_Rate = -100.0f;
}

void SoundManager::muteQuicklyJukeBox() {
	m_Track1.setVolume(0);
}

void SoundManager::unmuteJukeBox() {
	m_ChangingJukeBox = true;
	m_Rate = 100.0f;
}

void SoundManager::playBossTrack() {
	m_BossTrack.play();
}

void SoundManager::stopBossTrack() {
	m_BossTrack.stop();
}

void SoundManager::startAlarm() {
	m_AlarmS.play();
}

void SoundManager::stopAlarm() {
	m_AlarmS.stop();
}

void SoundManager::update(float dt) {
	if (m_ChangingJukeBox) {
		m_CurrentVolume = m_Track1.getVolume();
		m_Track1.setVolume(std::max(0.0f, std::min(m_CurrentVolume + m_Rate * dt, 30.0f)));
		if (m_Track1.getVolume() > 29.9f || m_Track1.getVolume() <= 0.0f) {
			m_ChangingJukeBox = false;
		}
	}
}