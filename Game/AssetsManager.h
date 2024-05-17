#pragma once

#include <map>
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"



class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	TTF_Font* getFont(std::string id, int size);

	//gameobjects

	void CreateBanana(Vector2D pos, int scale);

//	void AddFont(std::string id, std::string path, int fontSize);
//	TTF_Font* GetFont(std::string id);

private:

	Manager* manager;
	
//	std::map<std::string, TTF_Font*> fonts;
};