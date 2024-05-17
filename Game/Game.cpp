#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetsManager.h"


Map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);
TextureManager* Game::TexManager = new TextureManager;

auto& Player(manager.addEntity());
auto& wall(manager.addEntity());
auto& banan(manager.addEntity());


Game::Game(){

}
Game::~Game(){

}
/* it initializes. */
void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen){
	int flags = 0;
	if (fullscreen == true) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL initiali<ed" << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}	
		if (TTF_Init() == 0) {
			std::cout << "TTF initialized" << std::endl;
		}
		if (IMG_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cout << "IMG initialized" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	TexManager->AddTexture("Banana", "assets/Food/banan.png");
	TexManager->AddTexture("Player", "assets/player32.png");
	TexManager->AddTexture("Dirt", "assets/map/dirt.png");

	map = new Map();

	Player.addComponent<TransformComponent>(2);
	Player.addComponent<SpriteComponent>("Player");
	Player.addComponent<KeyboardController>();	
	Player.addComponent<ColliderComponent>("Player");
	Player.addComponent<HungerComponent>(SDL_GetTicks(), 100, 1000, 1);
	Player.addGroup(Game::groupPlayers);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 32, 32, 1);
	wall.addComponent<SpriteComponent>("Dirt");
	wall.addComponent<ColliderComponent>("wall");

	wall.addGroup(Game::groupFood);

	assets->CreateBanana(Vector2D(300, 140), 1);
	assets->CreateBanana(Vector2D(600, 120), 1);
	assets->CreateBanana(Vector2D(200, 350), 1);
	assets->CreateBanana(Vector2D(400, 500), 1);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& foods(manager.getGroup(Game::groupFood));

/* Read the fucking name */
void Game::handleEvents()
{

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
		}
	default:
		break;
	}
}
/* The Game logic and shit */
void Game::update(){

	manager.refresh();
	manager.update();
	Player.getComponent<HungerComponent>().LoseHunger(SDL_GetTicks());
	for (auto& c : colliders) {
		if (Player.hasComponent<ColliderComponent>() == true and c->hasComponent<ColliderComponent>() == true) {
			if (Collision::AABB(Player.getComponent<ColliderComponent>().collider, c->getComponent<ColliderComponent>().collider) == true) {
				std::cout << "Wall Hit" << std::endl;
			}
		}
	}
	for (auto& f : foods) {
		if (f->isActive() == true) {
			if (Collision::AABB(Player.getComponent<ColliderComponent>().collider, f->getComponent<ColliderComponent>().collider)){
				f->getComponent<DialogtextComponent>().setRender(true);
				if (Player.getComponent<KeyboardController>().pickUp == true) {
					Player.getComponent<HungerComponent>().addHunger(f->getComponent<FoodComponent>().Eat());
					f->destroy();
				}
			}
			else {
				if (f->hasComponent<DialogtextComponent>() == true) {
					f->getComponent<DialogtextComponent>().setRender(false);
				}
			}
		}
	}
}
/* It renders. What did you think */
void Game::render(){
	SDL_RenderClear(renderer);
	/* ADD STUFF TO RENDER */
	map->DrawMap();
	for (auto& t : tiles){
		t->draw();
	}

	for (auto& c : colliders){
		c->draw();
	}

	for (auto& p : players){
		p->draw();
	}
	for (auto& f : foods){
		f->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::QuitGame() {
	isRunning = false;
}

/* IT says Kill Your Self to SDL and exits the game */
void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}