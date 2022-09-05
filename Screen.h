#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "GameState.h"
#include "TextureManager.h"
#include "PanelManager.h"
#include "InputHandler.h"
#include "ScreenRemote.h"
#include "Fader.h"
#include "AI.h"
#include "SoundManager.h"

using namespace sf;

typedef std::shared_ptr<std::map<std::string, std::shared_ptr<Panel>>> Panel_Map;

class Screen {
protected:
	std::shared_ptr<AI> m_AI;

	std::shared_ptr<GameState> m_GameState;
	Vector2f m_Resolution;
	Panel_Map m_Panels;
	std::shared_ptr<PanelManager> m_PM;
	std::unique_ptr<InputHandler> m_InputHandler = nullptr;
	std::shared_ptr<ScreenRemote> m_ScreenRemote;
	std::shared_ptr<Fader> m_Fader;
	std::shared_ptr<SoundManager> m_SM;

public:
	View m_View;

	Screen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM);
	virtual void initialize() {};
	void addPanel(std::string name, std::string background, Vector2f centerPosition);
	void handleInput(RenderWindow& window);

	virtual void update(float dt);
	virtual void draw(RenderWindow& window);
};