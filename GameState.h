#pragma once
#include <iostream>

class GameState {
private:
	bool m_GameStarted;

	std::string m_Action;

	std::string m_PlayerName;

	bool m_LightState;
	bool m_PuzzleOneComplete;
	bool m_PuzzleTwoComplete;
	bool m_PuzzleThreeComplete;
	bool m_GotKey;
	bool m_GotKeycard;
	bool m_BigButtonPushed;
	bool m_ChallengeDecision;
	bool m_AIChallenged;
	bool m_AIDefeated;
	bool m_AIKilled;
	bool m_AISpared;
	bool m_AISaved;
	bool m_PlayerKilled;
	bool m_CyberspaceTravelled;
	bool m_PlayerWantsToHelp;
	bool m_AIAngered;
	
	int m_Scene;

public:
	GameState();

	//Setters
	void startGame();
	void setPlayerName(std::string name);
	void setLightState(bool state);
	void setPuzzleState(int puzzle, bool state);
	void getKey();
	void getKeycard();
	void pushBigButton();
	void challengeAI();
	void dontChallengeAI();
	void defeatAI();
	void spareAI();
	void killAI();
	void saveAI();
	void travelToCyberspace();
	void helpAI();
	void angerAI();
	void nextScene();
	void actCommander(std::string action);

	//Getters
	std::string getPlayerName();
	bool gameStarted();
	bool getLightState();
	bool getPuzzleState(int puzzle);
	bool gotKey();
	bool gotKeycard();
	bool bigButtonPushed();
	bool challengeDecisionMade();
	bool AIDefeated();
	bool AIChallenged();
	bool AISpared();
	bool AIKilled();
	bool AISaved();
	bool cyberspaceTravelled();
	bool playerWantsToHelp();
	bool AIAngered();
	int getScene();

	std::string getAction();
};