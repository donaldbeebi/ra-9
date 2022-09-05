#pragma once
#include "Battleground.h"
#include "AI.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

enum class stage { intro, healthreport, menu, fight, fightreport, item, itemreport, AI, AIreport, end, kill };

class Judge {
private:
	Battleground m_BG;
	DialogueComponent m_DC;
	bool m_GameStarted;
	stage m_Stage;
	bool m_Waiting;
	std::string m_Action;
	std::shared_ptr<AI> m_AI;
	int m_Section;
	int m_AIAttackSequence;
	Clock m_Clock;
	float m_CurrentTime;

public:
	Judge(std::shared_ptr<AI> AI);
	void startGame();

	void act(int button);
	void update();

	DialogueLine getDialogueLine();
	void triggerStage(stage stage);

	void returnToMainMenu();
	stage getCurrentStage();
};