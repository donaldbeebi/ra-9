#include "GameCommander.h"

void GameCommander::actGameState(std::string action) {
	if (action == "puzzle_one_complete") {
		findObject("door_lightbulb_room_abandoned_room")->disableDC();
	}
	else if (action == "puzzle_two_complete") {
		findObject("door_password_room_final_room")->disableDC();
	}
}