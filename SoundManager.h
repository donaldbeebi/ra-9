#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

using namespace sf;

class SoundManager {
private:
	static SoundBuffer m_BlipB;
	static Sound m_BlipS;
	
	static SoundBuffer m_ClickB;
	static Sound m_ClickS;
	static SoundBuffer m_ClockB;
	static Sound m_ClockS;

	static SoundBuffer m_SwitchPushB;
	static Sound m_SwitchPushS;
	static SoundBuffer m_SwitchReleaseB;
	static Sound m_SwitchReleaseS;

	static SoundBuffer m_ButtonPushB;
	static Sound m_ButtonPushS;
	static SoundBuffer m_ButtonReleaseB;
	static Sound m_ButtonReleaseS;

	static SoundBuffer m_BigButtonPushB;
	static Sound m_BigButtonPushS;
	static SoundBuffer m_BigButtonReleaseB;
	static Sound m_BigButtonReleaseS;

	static SoundBuffer m_hitAIB;
	static Sound m_hitAIS;
	static SoundBuffer m_hitAICriticalB;
	static Sound m_hitAICriticalS;
	static SoundBuffer m_hitPlayerB;
	static Sound m_hitPlayerS;

	static SoundBuffer m_AlarmB;
	static Sound m_AlarmS;
	static SoundBuffer m_RiserB;
	static Sound m_RiserS;

	static SoundBuffer m_HealB;
	static Sound m_HealS;

	static Music m_Track1;
	static Music m_BossTrack;

	static bool m_ChangingJukeBox;
	static float m_Rate;
	static float m_CurrentVolume;

public:
	SoundManager();

	static void play(std::string sound);
	static void startJukeBox();
	static void switchJukeBox();
	static void stopJukeBox();
	static void toggleJukeBox();
	static void updateJukeBoxStickGame();
	static void updateJukeBoxCyberspace(Vector2f location);
	static void muteJukeBox();
	static void muteQuicklyJukeBox();
	static void unmuteJukeBox();
	static void playBossTrack();
	static void stopBossTrack();
	
	static void startAlarm();
	static void stopAlarm();

	//void playFire(Vector2f emitterLocation, Vector2f listenerLocation);

	static void update(float dt);
};

