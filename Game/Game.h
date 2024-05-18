#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

class AssetManager;
class TextureManager;

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	
	void handleEvents();

	void update();

	void render();

	void clean();

	void QuitGame();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static AssetManager* assets;
	static TextureManager* TexManager;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupFood
	};

private:

	bool isRunning;
	SDL_Window *window;

};

#endif /* Game_hpp */