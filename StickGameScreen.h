#pragma once
#include "Screen.h"
#include "GameMaster.h"
#include "GameObject.h"
#include "StickGameCommander.h"
#include "StickGamePanelManager.h"
#include "Stick.h"
#include "StickGameInputHandler.h"
#include "Fader.h"

class StickGameScreen : public Screen {
private:
	bool m_Started;
	Sprite m_Background;
	Sprite m_Table;
	std::shared_ptr<Fader> m_Fader;
	std::shared_ptr<GameMaster> m_GameMaster;
	std::shared_ptr<StickGameCommander> m_Commander;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;

public:
	StickGameScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM);
	virtual void initialize() override;

	virtual void update(float dt) override;
	virtual void draw(RenderWindow& window) override;
};