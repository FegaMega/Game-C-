#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include <map>
#include "../AssetsManager.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool render;
public:
	SpriteComponent() = default;
	SpriteComponent(std::string id) {
		setTex(id);
		render = true;
	}
	~SpriteComponent() {}
	void setTex(std::string id) {
		texture = Game::TexManager->GetTexture(id);
		render = true;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}
};