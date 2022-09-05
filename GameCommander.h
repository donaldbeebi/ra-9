#pragma once
#include <memory>
#include <vector>
#include <list>
#include "Commander.h"
#include "InteractionManager.h"
#include "ObjectLoader.h"
#include "LayerManager.h"
#include "GameState.h"
#include "Panel.h"
#include "GameObject.h"
#include "Player.h"
#include "Enums.h"
#include "Fader.h"
#include "Puzzle.h"
#include "DialogueManager.h"
#include "SaveAISequence.h"
#include "ScreenShaker.h"

class GameCommander : public Commander {
private:
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<AI> m_AI;
	std::shared_ptr<Tilemap> m_Tilemap;
	std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> m_GameObjects;
	std::shared_ptr<std::vector<std::shared_ptr<Puzzle>>> m_Puzzles;
	std::shared_ptr<Fader> m_Fader;
	std::shared_ptr<Fader> m_WhiteFader;
	std::shared_ptr<Shaker> m_Shaker;
	std::shared_ptr<SaveAISequence> m_SAIS;
	std::shared_ptr<InteractionManager> m_IM;
	std::shared_ptr<LayerManager> m_LM;
	std::shared_ptr<DialogueManager> m_DM;

	//for interactions
	bool m_AttemptingInteraction;
	bool m_Interacting;
	bool m_Interacted;
	bool m_InteractionDisabled;
	int m_CurrentObjectIndex;
	std::shared_ptr<GameObject> m_CurrentObject; //Object we are interacting with
	std::shared_ptr<GameObject> m_CurrentObject2;

	//for changing levels
	bool m_ChangingLevel;
	std::string m_LevelToChange;
	std::shared_ptr<ObjectLoader> m_OL;

	//feedback
	std::string m_CurrentAction;
	
	//internal functions
	std::shared_ptr<GameObject> findObject(std::string name);
	std::shared_ptr<Puzzle> findPuzzle(std::string name);
	
public:
	GameCommander(std::shared_ptr<Player> player, std::shared_ptr<AI> ai, std::shared_ptr<ObjectLoader> OL,
		std::shared_ptr<std::vector<std::shared_ptr<Puzzle>>> puzzles,
		std::shared_ptr<InteractionManager> IM, std::shared_ptr<Tilemap> tilemap, std::shared_ptr<LayerManager> LM,
		std::shared_ptr<DialogueManager> DM, std::shared_ptr<GameState> gameState, std::shared_ptr<ScreenRemote> screenRemote,
		std::shared_ptr<Fader> fader, std::shared_ptr<Fader> whiteFader, std::shared_ptr<Shaker> shaker);
	
	//interactions
	void actAI(std::string action);
	bool actObject(std::string action);
	virtual void actPanel(std::string action) override;
	void actGameState(std::string action);
	void changeLevel(std::string targetLevel);
	void preparePuzzles();

	//player's input
	void pushInteraction();
	void releaseInteraction();
	void movePlayer(Direction direction);
	
	//interaction check
	void checkAI();
	void checkGameState();
	void checkInteractiveObjects();
	void checkIfPlayerOutOfInteractionRange();
	void checkLevelChange();
	void updateGameState();

	void update(float dt);

	//feedback
	virtual std::string getPanelAction() override; //Panel Manager will call this function

};