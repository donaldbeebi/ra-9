#pragma once
#include "StandardObject.h"

class BarTable : public StandardObject {
public:
	BarTable(std::string name, Vector2f initialCenterPosition);
};
