#include "GameCommander.h"

bool GameCommander::actObject(std::string action) {
	/*********************
	******** Main ********
	*********************/
	if (action == "door_main_lightbulb_room_push") {
		changeLevel("lightbulb_room");
		return true;
	}
	else if (action == "door_main_bar_push") {
		changeLevel("bar");
		return true;
	}
	else if (action == "door_main_library_push") {
		changeLevel("library");
		return true;
	}
	else if (action == "door_main_bedroom_push") {
		changeLevel("bedroom");
		return true;
	}
	else if (action == "door_main_password_room_push") {
		changeLevel("password_room");
		return true;
	}
	
	/*********************
	********* Bar ********
	*********************/
	else if (action == "door_bar_main_push") {
		changeLevel("main");
		return true;
	}

	/*********************
	****** Bedroom *******
	*********************/
	else if (action == "door_bedroom_main_push") {
		changeLevel("main");
		return true;
	}

	/*********************
	****** Library *******
	*********************/
	else if (action == "door_library_main_push") {
		changeLevel("main");
		return true;
	}

	/*********************
	*** Lightbulb Room ***
	*********************/
	else if (action == "door_lightbulb_room_main_push") {
		changeLevel("main");
		return true;
	}

	else if (action == "door_lightbulb_room_abandoned_room_push") {
		changeLevel("abandoned_room");
		return true;
	}

	else if (action == "lever1_push") {
		m_CurrentObject = findObject("lightbulb1");
		m_CurrentObject->getGC()->toggleState(0, 1);
		m_CurrentObject = findObject("lightbulb2");
		m_CurrentObject->getGC()->toggleState(0, 1);
		return true;
	}

	else if (action == "lever2_push") {
		m_CurrentObject = findObject("lightbulb2");
		m_CurrentObject->getGC()->toggleState(0, 1);
		m_CurrentObject = findObject("lightbulb3");
		m_CurrentObject->getGC()->toggleState(0, 1);
		return true;
	}

	else if (action == "lever3_push") {
		m_CurrentObject = findObject("lightbulb3");
		m_CurrentObject->getGC()->toggleState(0, 1);
		m_CurrentObject = findObject("lightbulb4");
		m_CurrentObject->getGC()->toggleState(0, 1);
		return true;
	}

	else if (action == "lever4_push") {
		m_CurrentObject = findObject("lightbulb4");
		m_CurrentObject->getGC()->toggleState(0, 1);
		m_CurrentObject = findObject("lightbulb5");
		m_CurrentObject->getGC()->toggleState(0, 1);
		return true;
	}

	/*********************
	*** Abandoned Room ***
	*********************/
	else if (action == "door_abandoned_room_lightbulb_room_push") {
		changeLevel("lightbulb_room");
		return true;
	}

	/*********************
	*** Password Room ****
	*********************/
	else if (action == "door_password_room_main_push") {
		changeLevel("main");
		return true;
	}

	else if (action == "door_password_room_final_room_push") {
		changeLevel("final_room");
		return true;
	}

	else if (action.find("number_button") != std::string::npos) {
		if (action.find("release") != std::string::npos) {
			findPuzzle("number_puzzle")->input(action[13]);
		}
		return true;
	}

	/*********************
	***** Final Room *****
	*********************/
	else if (action == "door_final_room_password_room_push") {
		changeLevel("password_room");
		return true;
	}

	else if (action == "bigbutton_push") {
		SoundManager::startAlarm();
		m_GameState->saveAI();
		return true;
	}

	else if (action == "none") {
		return true;
	}

	return false;
}