#pragma once
#include <memory>
#include <queue>
#include <string>
#include "Activity.h"
#include "CActivity.h"
#include "GameState.h"
#include "Trigger.h"
#include "TimeTrigger.h"
#include "GameStateTrigger.h"
#include "GameStartTrigger.h"
#include "LocationTrigger.h"
#include "NoPanelTrigger.h"
#include "ImmediateTrigger.h"
#include "CharacterDialogueComponent.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "PanelManager.h"

class AIState {
private:
	std::queue<Activity*> m_Activities;
	std::shared_ptr<GameState> m_GameState;
	std::shared_ptr<CharacterDialogueComponent> m_DC;
	std::string m_Action;
	std::shared_ptr<GameObject> m_Player;
	std::shared_ptr<Tilemap> m_Tilemap;
	std::shared_ptr<PanelManager> m_CyberPM;
	std::shared_ptr<PanelManager> m_BattlePM;
	std::shared_ptr<DialogueComponent> m_FightChat;

public:
	AIState(std::shared_ptr<GameState> gameState, std::shared_ptr<CharacterDialogueComponent> DC, std::shared_ptr<DialogueComponent> FightChat);

	void prepareForBattle(std::shared_ptr<PanelManager> battlePM);
	void prepareForCyberspace(std::shared_ptr<GameObject> player, std::shared_ptr<Tilemap> tilemap, std::shared_ptr<PanelManager> PM);

	void update();
	void act(std::string action);

	std::string getAction(); //For commander
};