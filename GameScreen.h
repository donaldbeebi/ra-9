//IMPLEMENT - a text file to store all the game objects locations
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GamePanelManager.h"
#include "Tilemap.h"
#include "InteractionManager.h"
#include "ObjectHeaders.h"
#include "Screen.h"
#include "GameInputHandler.h"
#include "GameCommander.h"
#include "CollisionHandler.h"
#include "LayerManager.h"
#include "ObjectLoader.h"
#include "Fader.h"
#include "Puzzle.h"
#include "LightPuzzle.h"
#include "NumberPuzzle.h"
#include "KeyPuzzle.h"
#include "Debugger.h"
#include "ScreenShaker.h"

using namespace sf;

class GameScreen: public Screen {
private:
	View m_HUD;

	std::shared_ptr<Tilemap> m_Tilemap;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::shared_ptr<std::vector<std::shared_ptr<Puzzle>>> m_Puzzles;

	std::shared_ptr<ObjectLoader> m_OL;
	std::shared_ptr<LayerManager> m_LM;
	std::shared_ptr<GameCommander> m_Commander;
	std::shared_ptr<InteractionManager> m_IM;
	std::unique_ptr<CollisionHandler> m_CH;
	std::shared_ptr<DialogueManager> m_DM;

	std::shared_ptr<Fader> m_WhiteFader;
	std::shared_ptr<Shaker> m_Shaker;

	Debugger m_Debugger;
	Vector2f tilePosition(Vector2f tilePosition);

public:
	GameScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM);
	virtual void initialize() override;

	virtual void update(float dt) override;
	virtual void draw(RenderWindow& window) override;
};