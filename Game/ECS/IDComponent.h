#pragma once

#include "Components.h"
#include "ECS.h"

class FoodComponent : public Component {

public:

	FoodComponent(char* ID) {
		id = ID;
	}
	~FoodComponent() {}

private:

	char* id;
};