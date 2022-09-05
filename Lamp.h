#pragma once
#include "StandardObject.h"

class Lamp : public StandardObject {
public:
	Lamp(std::string name, Vector2f initialCenterPosition);
};