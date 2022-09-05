#pragma once
#include "StandardObject.h"

class Cylinder : public StandardObject {
public:
	Cylinder(std::string name, Vector2f initialCenterPosition);
};