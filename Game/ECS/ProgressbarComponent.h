#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include <map>
#include "../AssetsManager.h"
#include "iostream"

class ProgressbarComponent : public Component {
private:
	SDL_Color color, boarderColor;
	int scale;
	SDL_Rect boarderDest;
	SDL_Rect progressDest;
	int progress;
	const int boarderWidth = 3;

public:
	ProgressbarComponent() {}

	ProgressbarComponent(int x, int y, int w, int h, int P, int Scale, SDL_Color Color) {
		color = Color;
		boarderColor = SDL_Color{ 10, 10, 10 };
		scale = Scale;
		progress = P;

		boarderDest.x = x;
		boarderDest.y = y;
		boarderDest.w = w*scale;
		boarderDest.h = h*scale;



		progressDest.x = x+boarderWidth;
		progressDest.y = y+ boarderWidth;
		progressDest.w = ( ( (w - boarderWidth * 2) / 100 ) * progress ) * scale;
		progressDest.h = ( h - ( boarderWidth * 2 ) ) * scale;

		// not worky worky


	}
	~ProgressbarComponent() {}

	void updateProgress(int P) {
		progress = P;
		progressDest.w = ( ( boarderDest.w - boarderWidth*2) / 100 ) * progress * scale;
	}

	void draw() {
		TextureManager::Draw(&boarderDest, boarderColor);
		TextureManager::Draw(&progressDest, color);
	}



};