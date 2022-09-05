#pragma once
#include "StickGame.h"
#include "DialogueComponent.h"
#include "GameObject.h"
#include "stdlib.h"
#include "AI.h"
#include <memory>
#include <vector>
#include "GameState.h"

enum class phase { menu, stick, board, bad, random, AI, noAI, noresponse, chatCD, gameover, confirm, chat, other, exit};

class GameMaster {
private:
	StickGame m_SG;
	DialogueComponent m_DC;
	DialogueComponent m_Chat;
	bool m_GameStarted;
	phase m_Phase;
	bool m_Waiting;
	std::string m_Action;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::shared_ptr<AI> m_AI;
	std::shared_ptr<GameState> m_GameState;

	int m_ChatSection;
	int m_ChatSectionOffset;
	int m_ChatOption; //REMOVE
	bool m_PlayerSaidSomething;
	bool m_IsDark;
	bool m_UnwillingToTalk;

public:
	GameMaster(std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> gameObjects, std::shared_ptr<AI> AI, std::shared_ptr<GameState> gameState);
	void startGame();

	void lightIsOn(bool state);
	void act(int button);
	void update();
	void triggerPhase(phase phase);
	phase getCurrentPhase();

	DialogueLine getDialogueLine();
	void calculateChatSection(int button);

	void returnToMainMenu();
};