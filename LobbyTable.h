#pragma once
#include "StandardObject.h"

class LobbyTable : public StandardObject {
public:
	LobbyTable(std::string name, Vector2f initialCenterPosition);
};
