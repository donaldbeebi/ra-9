#pragma once
#include "Screen.h"
#include "TitleInputHandler.h"
#include "TitleCommander.h"
#include "TitlePanelManager.h"
#include "Fader.h"

using namespace sf;

class TitleScreen : public Screen {
private:
	Sprite m_Background;
	std::shared_ptr<TitleCommander> m_Commander;

public:
	TitleScreen(Vector2f resolution, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote, std::shared_ptr<AI> AI, std::shared_ptr<SoundManager> SM);

	virtual void update(float dt) override;
	virtual void draw(RenderWindow& window) override;

	virtual void initialize() override;
};