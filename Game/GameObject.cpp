#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int intputX, int inputY) {

	objTexture = TextureManager::LoadTexture(texturesheet);
	x = intputX;
	y = inputY;
}

void GameObject::Update() {
	x++;
	y++;
	scale = 2;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = 32 * scale;
	destRect.w = 32 * scale;
	destRect.x = x;
	destRect.y = y;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}