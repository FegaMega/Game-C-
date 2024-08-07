#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char *FileName)
{ 
	SDL_Surface* tempSurface = IMG_Load(FileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

void TextureManager::Draw(SDL_Rect* dest, SDL_Color color)
{
	SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Game::renderer, dest);
}

void TextureManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}


