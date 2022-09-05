#pragma once
#include <map>
#include <iostream>
#include "TextureManager.h"
#include "Screen.h"
#include "TitleScreen.h"
#include "StickGameScreen.h"
#include "GameScreen.h"
#include "BattleScreen.h"
#include "GameState.h"
#include "ScreenRemote.h"
#include "AI.h"
#include "SoundManager.h"

class ScreenManager {
private:
	std::shared_ptr<SoundManager> m_SM;
	std::shared_ptr<AI> m_AI;
	std::shared_ptr<GameState> m_GameState;
	std::map<std::string, std::unique_ptr<Screen>> m_Screens;
	std::string m_CurrentScreen;
	TextureManager m_TextureManager;
	Vector2f m_Resolution;
	std::shared_ptr<ScreenRemote> m_ScreenRemote;
	RenderWindow& m_Window;
	Fader m_Fader;
	std::string m_CurrentAction;
	View m_View;

public:
	ScreenManager(Vector2f resolution, RenderWindow& window);
	void actRemote();
	void handleInput();
	void update(float dt);
	void draw();

};