#pragma once

#include "Game.h"
#include <map>
#include <string>
#include <iostream>

class TextureManager {
public:
	TextureManager(){}
	~TextureManager(){}
	static SDL_Texture* LoadTexture(const char *fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void Draw(SDL_Rect* dest, SDL_Color color);
	void AddTexture(std::string id, const char* path);
	
	SDL_Texture* GetTexture(std::string id) {
		return textures[id];
	}
private:

	std::map<std::string, SDL_Texture*> textures;

};