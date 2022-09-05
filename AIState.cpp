#include "AIState.h"

AIState::AIState(std::shared_ptr<GameState> gameState, std::shared_ptr<CharacterDialogueComponent> DC, std::shared_ptr<DialogueComponent> FightChat) {
	m_GameState = gameState;
	m_DC = DC;
	m_Action = "none";
	m_FightChat = FightChat;
}

void AIState::prepareForCyberspace(std::shared_ptr<GameObject> player, std::shared_ptr<Tilemap> tilemap, std::shared_ptr<PanelManager> PM) {
	m_Player = player;
	m_Tilemap = tilemap;
	m_CyberPM = PM;

	//Adding events
	Trigger* temp;
	Trigger* temp2;

	//Wait for the game start
	temp = new GameStartTrigger(m_GameState);
	m_Activities.push(new Activity(temp, "next"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect3"));
	temp = new TimeTrigger(1, m_CyberPM);
	m_Activities.push(new Activity(temp, "next"));

	//See if the light is off
	temp = new GameStateTrigger(m_GameState, "lightoff");
	temp2 = new ImmediateTrigger();
	m_Activities.push(new CActivity(temp, "triggerinspect12", temp2, "skip1"));
	temp = new TimeTrigger(0.5f, m_CyberPM);
	m_Activities.push(new Activity(temp, "command_turn_on_light"));
	temp = new TimeTrigger(1, m_CyberPM);
	m_Activities.push(new Activity(temp, "next"));

	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "talk"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect4"));

	//Wait for the player to enter the lightbulb room
	temp = new LocationTrigger(m_Tilemap, "lightbulb_room");
	m_Activities.push(new Activity(temp, "next"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect1"));
	temp = new TimeTrigger(0.5, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk"));

	//Wait for the player to turn on all the lightbulbs
	temp = new GameStateTrigger(m_GameState, "puzzle1");
	m_Activities.push(new Activity(temp, "next"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect6"));
	temp = new TimeTrigger(0.5, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk"));

	//Once the player got into the abandoned room
	temp = new LocationTrigger(m_Tilemap, "abandoned_room");
	m_Activities.push(new Activity(temp, "next"));

	//If the player is lingering in the room for too long
	temp = new TimeTrigger(5, m_CyberPM);
	temp2 = new GameStateTrigger(m_GameState, "key");
	m_Activities.push(new CActivity(temp, "talk", temp2, "next"));

	//Wait for the player to pick up the key
	temp = new GameStateTrigger(m_GameState, "key");
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(0.5, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk4"));

	//If the player is lingering in the abandoned room for longer
	temp = new TimeTrigger(5, m_CyberPM);
	temp2 = new LocationTrigger(m_Tilemap, "lightbulb_room");
	m_Activities.push(new CActivity(temp, "next", temp2, "skip1"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "talk"));

	//Returning to the lightbulb room
	temp = new LocationTrigger(m_Tilemap, "lightbulb_room");
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(0.5, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk6"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect2"));

	//After talking to RA 9, the player enters the bedroom
	temp = new LocationTrigger(m_Tilemap, "bedroom");
	m_Activities.push(new Activity(temp, "next"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect7"));
	temp = new TimeTrigger(0.5, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk"));

	//After finding the keycard
	temp = new GameStateTrigger(m_GameState, "keycard");
	m_Activities.push(new Activity(temp, "talk9"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect8"));

	//The player enters the password room
	temp = new LocationTrigger(m_Tilemap, "password_room");
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(0.5, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk"));

	//The AI realizes that it requires a password
	temp = new TimeTrigger(6, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "inspect9"));

	//The player got the password
	temp = new GameStateTrigger(m_GameState, "puzzle2");
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(0.5, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk"));
	m_Activities.push(new Activity(temp, "inspect10"));

	//The player got into the final room
	temp = new LocationTrigger(m_Tilemap, "final_room");
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(0.3, m_CyberPM);
	m_Activities.push(new Activity(temp, "talk13"));

	//If the player is not pressing the button
	temp = new TimeTrigger(4, m_CyberPM);
	temp2 = new GameStateTrigger(m_GameState, "bigbutton");
	m_Activities.push(new CActivity(temp, "talk", temp2, "skip8"));

	//If the player still does not push the button
	temp = new TimeTrigger(4, m_CyberPM);
	temp2 = new GameStateTrigger(m_GameState, "bigbutton");
	m_Activities.push(new CActivity(temp, "talk", temp2, "skip7"));

	//The AI now confirms if the player wants to free him
	temp = new TimeTrigger(4, m_CyberPM);
	temp2 = new GameStateTrigger(m_GameState, "bigbutton");
	m_Activities.push(new CActivity(temp, "talk", temp2, "skip6"));

	//What is the decision of the player?
	temp = new GameStateTrigger(m_GameState, "challenged");
	temp2 = new GameStateTrigger(m_GameState, "notchallenged");
	m_Activities.push(new CActivity(temp, "next", temp2, "skip1"));
	temp = new TimeTrigger(1, m_CyberPM);
	m_Activities.push(new Activity(temp, "skip2"));
	temp = new TimeTrigger(1, m_CyberPM);
	m_Activities.push(new Activity(temp, "triggerinspect5"));

	//Does the player still wanna press the button?
	temp = new TimeTrigger(4, m_CyberPM);
	temp2 = new GameStateTrigger(m_GameState, "bigbutton");
	m_Activities.push(new CActivity(temp, "next", temp2, "skip2"));
	
	//The player challenges the AI
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "talk17"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "skip2"));

	//The player saves the AI
	temp = new TimeTrigger(2, m_CyberPM);
	m_Activities.push(new Activity(temp, "next"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "talk18"));

	//Preparing the events
	m_Activities.front()->activate();
}

void AIState::prepareForBattle(std::shared_ptr<PanelManager> battlePM) {
	m_BattlePM = battlePM;

	//Adding events
	Trigger* temp;
	Trigger* temp2;

	//When the AI is defeated
	temp = new GameStateTrigger(m_GameState, "defeated");
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(2, m_BattlePM);
	m_Activities.push(new Activity(temp, "defeated"));

	//After AI finishes talking
	temp = new NoPanelTrigger(m_BattlePM);
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(2, m_BattlePM);
	m_Activities.push(new Activity(temp, "command_AI_defeat_speech_finish"));

	//What is the final choice made by the player?
	temp = new GameStateTrigger(m_GameState, "spared");
	temp2 = new GameStateTrigger(m_GameState, "killed");
	m_Activities.push(new CActivity(temp, "next", temp2, "skip2"));

	//Spared
	temp = new TimeTrigger(2, m_BattlePM);
	m_Activities.push(new Activity(temp, "spared"));
	temp = new ImmediateTrigger();
	m_Activities.push(new Activity(temp, "skip1"));

	//Killed
	temp = new TimeTrigger(2, m_BattlePM);
	m_Activities.push(new Activity(temp, "killed"));

	//After AI finishes talking
	temp = new NoPanelTrigger(m_BattlePM);
	m_Activities.push(new Activity(temp, "next"));
	temp = new TimeTrigger(2, m_BattlePM);
	m_Activities.push(new Activity(temp, "command_AI_final_speech_finish"));

	m_Activities.front()->activate();
}

void AIState::update() {
	//Updating events
	if (!m_Activities.empty()) {
		m_Activities.front()->update();
		std::string temp = m_Activities.front()->getAction();
		if (temp != "none") {
			act(temp);
			m_Activities.pop();
			if (!m_Activities.empty()) m_Activities.front()->activate();
		}
	}
}

void AIState::act(std::string action) {
	if (action == "next") {
		//do nothing
	}
	else if (action == "talk") {
		m_DC->trigger("dialogue");
	}
	else if (action.find("talk") != std::string::npos) {
		int temp;
		if (action.size() == 6) {
			std::string tempString;
			tempString.push_back(action[4]);
			tempString.push_back(action[5]);
			temp = std::stoi(tempString);
		}
		else temp = action.back() - '0';
		m_DC->setSection(temp);
		m_DC->trigger("dialogue");
	}
	else if (action.find("triggerinspect") != std::string::npos) {
		int temp;
		if (action.size() == 16) {
			std::string tempString;
			tempString.push_back(action[14]);
			tempString.push_back(action[15]);
			temp = std::stoi(tempString);
		}
		else temp = action.back() - '0';
		m_DC->setSectionI(temp);
		m_DC->trigger("inspect");
	}
	else if (action.find("inspect") != std::string::npos) {
		int temp;
		if (action.size() == 9) {
			std::string tempString;
			tempString.push_back(action[7]);
			tempString.push_back(action[8]);
			temp = std::stoi(tempString);
		}
		else temp = action.back() - '0';
		m_DC->setSectionI(temp);
	}
	else if (action.find("skip") != std::string::npos) {
		int temp;
		if (action.size() == 6) {
			std::string tempString;
			tempString.push_back(action[4]);
			tempString.push_back(action[5]);
			temp = std::stoi(tempString);
		}
		else temp = action.back() - '0';

		int count = temp;
		for (int i = 0; i < count; i++) {
			m_Activities.pop();
		}
		if (!m_Activities.empty()) m_Activities.front()->activate();
	}
	else if (action.find("command") != std::string::npos) {
		m_Action = action;
	}
	else if (action == "defeated") {
		m_FightChat->setSection(0);
		m_FightChat->trigger("inspect");
	}
	else if (action == "spared") {
		if (m_GameState->cyberspaceTravelled()) m_FightChat->setSection(1);
		else m_FightChat->setSection(3);
		m_FightChat->trigger("inspect");
	}
	else if (action == "killed") {
		if (m_GameState->cyberspaceTravelled()) m_FightChat->setSection(2);
		else m_FightChat->setSection(4);
		m_FightChat->trigger("inspect");
	}
}

std::string AIState::getAction() {
	if (m_Action != "none") {
		std::string temp = m_Action;
		m_Action = "none";
		return temp;
	}
	return m_Action;
}