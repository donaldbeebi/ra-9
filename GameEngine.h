#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
//#include <SoundEngine.h>

using namespace sf;

class GameEngine {
	Clock m_Clock;
	Time m_Time;
	RenderWindow m_Window;
	
	std::unique_ptr<ScreenManager> m_ScreenManager;

	Time m_DT;
	Vector2f m_Resolution;

	void handleInput();
	void update();
	void draw();

public:
	//SoundEngine m_SoundEngine;

	GameEngine();
	void run();

};