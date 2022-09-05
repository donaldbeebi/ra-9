#pragma once
#include "Character.h"
#include "Enums.h"

class Player : public Character {
public:
	Player(std::string name, Vector2f initialCenterPosition);
};