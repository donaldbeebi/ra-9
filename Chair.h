#pragma once
#include "StandardObject.h"

class Chair : public StandardObject {
public:
	Chair(std::string name, Vector2f initialCenterPosition);
};