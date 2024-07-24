#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "iostream"

class KeyboardController : public Component {
public:
	TransformComponent *transform;
	bool Use;
	bool pickUp;
	bool UseInventory;
	int Selected;
	void init() override {
		Use = false;
		pickUp = false;
		UseInventory = false;
		transform = &entity->getComponent<TransformComponent>();
	}

	bool getUse() { return Use; }
	bool getpickUp() { return pickUp; }
	bool getUseInventory() { return UseInventory; }

	void update() override {
		
		Use = false;
		pickUp = false;
		UseInventory = false;

		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym){
				case SDLK_w:
					if (transform->velocity.y >= 0) {
						transform->velocity.y -= 1;
					}
					break;
				case SDLK_a:
					if (transform->velocity.x >= 0) {
					transform->velocity.x -= 1;
					}
					break;
				case SDLK_s:
					if (transform->velocity.y <= 0) {
						transform->velocity.y += 1;
					}
					break;
				case SDLK_d:
					if (transform->velocity.x <= 0) {
						transform->velocity.x += 1;
					}
					break;
				case SDLK_e:
					Use = true;
					break;
				case SDLK_f:
					pickUp = true;
					break;
				case SDLK_q:
					UseInventory = true;
					break;
				case SDLK_1:
					Selected = 1;
					break;
				case SDLK_2:
					Selected = 2;
					break;
				case SDLK_3:
					Selected = 3;
					break;
				case SDLK_4:
					Selected = 4;
					break;
				case SDLK_5:
					Selected = 5;
					break;
				case SDLK_6:
					Selected = 6;
					break;
				case SDLK_7:
					Selected = 7;
					break;
				case SDLK_8:
					Selected = 8;
					break;
				case SDLK_9:
					Selected = 9;
					break;
				
				default:
					break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				if (transform->velocity.y <= 0) {
					transform->velocity.y += 1;
				}
				break;
			case SDLK_a:
				if (transform->velocity.x <= 0) {
					transform->velocity.x += 1;
				}
				break;
			case SDLK_s:
				if (transform->velocity.y >= 0) {
					transform->velocity.y -= 1;
				}
				break;
			case SDLK_d:
				if (transform->velocity.x >= 0) {
					transform->velocity.x -= 1;
				}
				break;
			default:
				break;
			}
		}
	}
};


