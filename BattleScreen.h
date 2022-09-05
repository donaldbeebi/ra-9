#pragma once
#include "Screen.h"
#include "BattleCommander.h"
#include "BattlePanelManager.h"
#include "BattleInputHandler.h"
#include "Judge.h"

class BattleScreen : public Screen {
private:
	std::shared_ptr<Judge> m_Judge;
	std::shared_ptr<BattleCommander> m_Commander;

public:
	BattleScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM);
	virtual void initialize() override;

	virtual void update(float dt) override;
	virtual void draw(RenderWindow& window);
};