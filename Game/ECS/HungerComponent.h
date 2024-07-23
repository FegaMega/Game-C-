#pragma once

#include "Components.h"
#include "stdint.h"

class HungerComponent : public Component {
private:
	
	float Hunger;
	int32_t Time;
	int LossRate;
	float LossAmount;
	bool render;
	SDL_Rect outsideScr, outsideDest;
	SDL_Rect insideScr, insideDest;
	//Needs SDL_Surface and a rendering code for it, also needs handling for the rects and makintg the correct colors and shit
	// PLS help
public:

	HungerComponent(int32_t time, float hunger, int lossRate, float lossAmount){
		Time = time;
		Hunger = hunger;
		LossRate = lossRate;
		LossAmount = lossAmount;
		render = true;
	}

 	float getHunger() { return Hunger; }
	float* getHungerPtr() { return &Hunger; }
	int32_t getTime() { return Time; }
	int getLossRate() { return LossRate; }
	float getLossAmount() { return LossAmount; }
	bool getRender() { return render; };

	void setRender(bool r) {
		render = r;
	}

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