#pragma once
#include "StandardObject.h"

class Table : public StandardObject {
public:
	Table(std::string name, Vector2f initialCenterPosition);
};