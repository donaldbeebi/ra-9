#include "GameCommander.h"

void GameCommander::actPanel(std::string action) {
	if (action == "command_test_true") {
		m_CurrentObject = findObject("test");
		m_CurrentObject->getGC()->toggle();
	}
	else if (action == "command_interactlever_true") {
		m_CurrentObject = findObject("test");
		m_CurrentObject->getIC()->forceInteract();
	}
	else if (action == "command_inspect_lightbulb") {
		m_CurrentAction = "open_dialogue";
		for (int i = 0; i != m_GameObjects->size(); i++) {
			if ((*m_GameObjects)[i]->getName().find("lightbulb") != std::string::npos) {
				if((*m_GameObjects)[i]->getName().find("room") == std::string::npos)
					(*m_GameObjects)[i]->getDC()->setSection(1);
			}
		}
	}
	else if (action == "command_read_true") {
		m_CurrentObject2->getDC()->setSection(1);
		m_CurrentObject2->getDC()->trigger("inspect");
	}
	else if (action == "command_read_false") {
		m_CurrentObject2->getDC()->setSection(2);
		m_CurrentObject2->getDC()->trigger("inspect");
	}
	else if (action == "command_read_finish") {
		m_CurrentObject2->getDC()->setSection(0);
	}
	else if (action == "command_find_true") {
		m_CurrentObject2->getDC()->setSection(2);
		m_CurrentObject2->getDC()->trigger("inspect");
	}
	else if (action == "command_find_false") {
		m_CurrentObject2->getDC()->setSection(3);
		m_CurrentObject2->getDC()->trigger("inspect");
	}
	else if (action == "command_find_finish") {
		m_CurrentObject2->getDC()->setSection(1);
	}
	else if (action == "command_find_key_true") {
		m_CurrentObject2->getDC()->setSection(2);
		m_CurrentObject2->getDC()->trigger("inspect");
	}
	else if (action == "command_find_key_false" && !findPuzzle("key_puzzle")->isComplete()) {
		m_CurrentObject2->getDC()->setSection(3);
		m_CurrentObject2->getDC()->trigger("inspect");
	}
	else if (action == "command_find_key_false" && findPuzzle("key_puzzle")->isComplete()) {
		m_CurrentObject2->getDC()->setSection(4);
		m_CurrentObject2->getDC()->trigger("inspect");
	}
	else if (action == "command_inspect_pony") {
		m_CurrentObject2->getDC()->setSection(1);
		m_AI->getDC()->trigger(action);
	}
	else if (action == "command_found_key") {
		findPuzzle("key_puzzle")->manualComplete();
		m_CurrentObject2->getDC()->setSection(1);
		m_OL->findObjectInAll("door_main_password_room")->getDC()->setSection(1);
		m_GameState->getKeycard();
	}
	else if (action == "command_unlock") {
		m_CurrentObject2->disableDC();
	}
	else if (action == "command_repeat") {
		m_CurrentObject2->getDC()->setSection(0);
	}
	else if (action == "command_key_pickup_true") {
		findObject("key")->getGC()->disable();
		findObject("key")->disableDC();
		m_GameState->getKey();
	}
	else if (action == "command_unlock_keycard") {
		m_CurrentObject2->disableDC();
	}
	else if (action == "command_unlock_bedroom") {
		m_OL->findObjectInAll("door_main_bedroom")->getDC()->setSection(1);
	}
	else if (action == "command_unlock_library") {
		m_OL->findObjectInAll("door_main_library")->getDC()->setSection(1);
	}
	else if (action == "command_big_button_true") {
		m_CurrentObject2->getIC()->forceInteract();
		m_GameState->pushBigButton();
		m_InteractionDisabled = true;
	}
	else if (action == "command_AI_confirm_false") {
		m_GameState->challengeAI();
		m_InteractionDisabled = true;
	}
	else if (action == "command_AI_not_saved") {
		m_GameState->challengeAI();
		m_ScreenRemote->switchScreen("Battle");
	}
	else if (action == "command_AI_confirm_true") {
		m_GameState->dontChallengeAI();
	}
	else if (action == "command_AI_saved") {
		//m_ScreenRemote->switchScreen("TitleScreen");
		m_SAIS->trigger();
	}
	else if (action == "command_jukebox_true") {
		SoundManager::startJukeBox();
	}
	else if (action == "command_jukebox_false") {
		SoundManager::stopJukeBox();
	}
	else if (action == "command_heal") {
		SoundManager::play("heal");
	}
}