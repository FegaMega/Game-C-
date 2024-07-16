#include "AssetsManager.h"
#include "ECS\Components.h"
#include "ECS\ECS.h"


AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}


void AssetManager::CreateBanana(Vector2D pos, int scale)
{
	auto& Banana(manager->addEntity());
	Banana.setID("Banana");
	Banana.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, scale);
	Banana.addComponent<SpriteComponent>("Banana");
	Banana.addComponent<FoodComponent>(20);
	Banana.addComponent<ColliderComponent>("Banana");
	Banana.addComponent<DialogtextComponent>();
	Banana.getComponent<DialogtextComponent>().setTex("Eat : E\nPick up : F");
	Banana.addGroup(Game::groupFood);

}

TTF_Font* AssetManager::getFont(std::string id, int size) {
	return TTF_OpenFont("assets/Fonts/vgasys.fon", size);
}

/*
void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}
*/