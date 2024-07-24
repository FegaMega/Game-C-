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
int itemComponent::getAmount() {
	return amount;
}

int InventoryComponent::findFirstEmptySlot() {
	// return of -1 means no empty slot exists
	int i = 0;
	if (items.size() > 0 and items.size() < 10)
		for (auto& item : items) {
			if (item->hasComponent<itemComponent>() == true) {
				if (item->getComponent<itemComponent>().getAmount() == 0) {
					return i;
				}
			}
			else {
				return i;
			}
			i++;
		}
	else {
		return -1;
	}
	return i;

}

int InventoryComponent::findItemWithSameID(std::string id) {
	// return of -1 means no item has the same ID
	int i = 0;
	if (items.size() > 0 and items.size() < 10)
		for (auto& item : items) {
			if (item->getID() == id) {
				return i;
			}
			i++;
		}
	return -1;
}

Entity& InventoryComponent::addEntity(int n, std::string id) {
	
	auto& item(manager->addEntity());

	item.setID(id);
	item.addGroup(inventory);
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
	if (item.getID() == "Apple") {
		item.addComponent<FoodComponent>(15);
	}
	
	return item;
}

Entity* InventoryComponent::addEntity(int n, Entity* e) {
	if (e->hasComponent<DialogtextComponent>() == false) {
		e->addComponent<DialogtextComponent>();
	}
	e->addComponent<itemComponent>(1, n);
	std::stringstream num;
	num << e->getComponent<itemComponent>().getAmount();
	e->getComponent<DialogtextComponent>().setTex(num.str().c_str());
	e->getComponent<DialogtextComponent>().setRender(true);
	e->getComponent<TransformComponent>().position.x = (float)80 + n * 48.0f;
	e->getComponent<TransformComponent>().position.y = 600;

	e->resetGroup();
	e->addGroup(inventory, n);

	items = manager->getGroup(inventory);

	std::cout << std::endl;
	return e;
}

void InventoryComponent::addItem(std::string id) {
	
	int n = findItemWithSameID(id);
	if (n >= 0) {
		
		items[n]->getComponent<itemComponent>().addAmount(1);
		std::stringstream num;
		num << items[n]->getComponent<itemComponent>().getAmount();
		items[n]->getComponent<DialogtextComponent>().setTex(num.str());
		return;
	}
	n = findFirstEmptySlot();
	if (n >= 0) {
		addEntity(n, id);
		return;
	}

	addEntity(Selected, id);

}

void InventoryComponent::addItem(Entity* e) {

	int n = findItemWithSameID(e->getID());
	if (n >= 0) {

		items[n]->getComponent<itemComponent>().addAmount(1);
		std::stringstream num;
		num << items[n]->getComponent<itemComponent>().getAmount();
		items[n]->getComponent<DialogtextComponent>().setTex(num.str());
		e->destroy();
		return;
	}
	n = findFirstEmptySlot();
	if (n >= 0) {
		
		addEntity(n, e);
		return;
	}
	// should throw old one at Selected 

	addEntity(Selected, e);
}

Entity* InventoryComponent::returnItem() {
	if ((int)items.size()-1 >= Selected){
		if (items[Selected]->hasComponent<itemComponent>() == true) {
			return items[Selected];
		}
		else {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}


void InventoryComponent::destroyItem(Entity* selected) {
	selected->resetComponent();
	selected->setID("");

}


void InventoryComponent::throwItem(Entity* selected) {
	//creates item on world then subtracts 1 from amount
	// if amount < 1 destroy the item 
}
