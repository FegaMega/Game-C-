#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "iostream"

class KeyboardController : public Component {
public:
	TransformComponent *transform;
	bool pickUp;
	void init() override {
		pickUp = false;
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		
		pickUp = false;
		
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
					pickUp = not pickUp;
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


