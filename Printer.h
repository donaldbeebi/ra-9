#pragma once
#include "StandardObject.h"

class Printer : public StandardObject {
public:
	Printer(std::string name, Vector2f initialCenterPosition);
};
