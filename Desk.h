#pragma once
#include "StandardObject.h"

class Desk : public StandardObject {
public:
	Desk(std::string name, Vector2f initialCenterPosition);
};