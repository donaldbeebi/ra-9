#include "GameCommander.h"

void GameCommander::actAI(std::string action) {
	if (action == "command_turn_on_light") {
		m_Fader->brighten();
	}
}