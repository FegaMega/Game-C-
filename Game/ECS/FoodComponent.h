#pragma once

#include "Components.h"
#include "ECS.h"

class FoodComponent : public Component {

public:
	


	FoodComponent(int Value) {
		foodValue = Value;
	}
	~FoodComponent() {}

	int Eat() {
		entity->destroy();
		return foodValue;

	}

private:

	int foodValue;
};