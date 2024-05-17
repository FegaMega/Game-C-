#pragma once

#include "Components.h"
#include "stdint.h"

class HungerComponent : public Component {
public:
	
	float Hunger;
	int32_t Time;
	int LossRate;
	float LossAmount;

	HungerComponent(int32_t time, float hunger, int lossRate, float lossAmount){
		Time = time;
		Hunger = hunger;
		LossRate = lossRate;
		LossAmount = lossAmount;
	}

	float getHunger() { return Hunger; }
	int32_t getTime() { return Time; }
	int getLossRate() { return LossRate; }
	float getLossAmount() { return LossAmount; }

	void addHunger(float a) {
		Hunger += a;
		if (Hunger > 100) {
			Hunger = 100;
		}
			
	}
	void subHunger(float a) {
		Hunger -= a;
		if (Hunger < 0) {
			Hunger = 0;
		}
	}

	void LoseHunger(int32_t time) {
		if (time - Time > LossRate) {
			Hunger -= LossAmount;
			Time = time;
		}
	}

};