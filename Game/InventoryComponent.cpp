#include "ECS/InventoryComponent.h"

void itemComponent::subAmount(int i) {
		amount -= i;
		std::stringstream num;
		num << amount;
		Dialogtext->setTex(num.str());
}
void itemComponent::addAmount(int i) {
	amount += i;
	std::stringstream num;
	num << amount;
	Dialogtext->setTex(num.str());
}


int InventoryComponent::findFirstEmptySlot(std::string id) {

	int s = NULL;
	int i = 0;
	for ( auto& item : items ) {
		if (item->hasComponent<itemComponent>() == true) {
			std::cout << "huh" << std::endl;
			std::cout << item->getComponent<itemComponent>().getAmount() << std::endl;
			if (item->getComponent<itemComponent>().getAmount() == 0) {
				return i;
			}

			if (item->getID() == id) {
				return i + 10;
			}

			std::cout << 1 << std::endl;

			return i + 20;
		}
		else {
			return i;
		}
		i += 1;
	}
}

Entity& InventoryComponent::addEntity(int n, std::string id) {
	
	auto& item(manager.addEntity());

	item.setID(id);
	items[n] = &item;
	item.addComponent<TransformComponent>((float)80 + n * 48.0f, 600, 32, 32, 1);
	item.addComponent<SpriteComponent>(id);
	item.addComponent<DialogtextComponent>();
	item.addComponent<itemComponent>(1, n); // gets DialogtextComponent so must be after
	std::stringstream num;
	num << item.getComponent<itemComponent>().getAmount();
	item.getComponent<DialogtextComponent>().setTex(num.str().c_str());
	item.getComponent<DialogtextComponent>().setRender(true);
	if (item.getID() == "Banana") {
		item.addComponent<FoodComponent>(20);
	}
	return item;
}

Entity& InventoryComponent::addEntity(int n, Entity* e) {

	auto& item(manager.addEntity());

	item.setID(e->getID());
	items[n] = &item;
	item.addComponent<itemComponent>(1, n);
	item.addComponent<TransformComponent>((float)80 + n * 48.0f, 600, 32, 32, 1);
	item.addComponent<SpriteComponent>(e->getID());
	item.addComponent<DialogtextComponent>();
	std::stringstream num;
	num << item.getComponent<itemComponent>().getAmount();
	item.getComponent<DialogtextComponent>().setTex(num.str().c_str());
	item.getComponent<DialogtextComponent>().setRender(true);
	if (e->hasComponent<FoodComponent>() == true) {
		item.addComponent<FoodComponent>(e->getComponent<FoodComponent>().getFoodValue());
	}
	return item;
}

void InventoryComponent::addItem(std::string id) {
	int n = findFirstEmptySlot(id);
	
	if (n < 10) {
		// should throw old one 
		// havent made that possible yet
		addEntity(n, id);

	}
	else if (n < 20) {
		// should throw old one 
		// havent made that possible yet
		
		items[n-10]->getComponent<itemComponent>().addAmount(1);
		std::stringstream num;
		num << items[n-10]->getComponent<itemComponent>().getAmount();
		items[n-10]->getComponent<DialogtextComponent>().setTex(num.str());
		
	}
	else {
		addEntity(Selected, id);
	}
}

void InventoryComponent::addItem(Entity* e) {
	int n = findFirstEmptySlot(e->getID());
	std::cout << n << std::endl;
	if (n < 10) {
		// should throw old one 
		// havent made that possible yet
		addEntity(n, e);

	}
	else if (n < 20) {
		// should throw old one 
		// havent made that possible yet

		items[n - 10]->getComponent<itemComponent>().addAmount(1);
		

	}
	else {
		addEntity(Selected, e);
	}
}

Entity* InventoryComponent::returnItem() {
	return items[Selected];
}

void InventoryComponent::destroyItem(Entity* selected) {
	selected->destroy();
	selected->delGroup(inventory);
}
