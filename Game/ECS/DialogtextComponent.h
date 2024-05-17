#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include <map>
#include "../AssetsManager.h"


class DialogtextComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect srcRect, destRect;
	bool render;
	const char* text;
	TTF_Font* font;

public:
	DialogtextComponent() {};
	
	~DialogtextComponent() {
		SDL_DestroyTexture(texture);
	}

	void init() override {
		font = Game::assets->getFont("System Fet", 25);
		transform = &entity->getComponent<TransformComponent>();
		 
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 0;
		srcRect.h = 0;	

		render = false;
	}
	
	void setTex(const char* text) {
		SDL_Color c = { 255, 255, 255, 0 };
		surface = TTF_RenderText_Solid(font, text, c);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
		destRect.w = srcRect.w * transform->scale;
		destRect.h = srcRect.h * transform->scale;
	}

	inline void setRender(bool r) { render = r; }
	inline bool getRender() { return render; }

	void update() override {
		destRect.x = transform->position.x + transform->width;
		destRect.y = transform->position.y;
	}

	void draw() override {
		if (render == true) {
			TextureManager::Draw(texture, srcRect, destRect);
		}
	}
};