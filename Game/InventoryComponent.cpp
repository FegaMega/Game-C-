#include "ECS/InventoryComponent.h"

int InventoryComponent::findFirstEmptySlot(std::string id) {

	int s = NULL;
	for (int i = 0; i < 10; i++) {
		if (items[i]->getComponent<itemComponent>().getAmount() == 0 and s != NULL) {
			s = i;
		}

		if (items[i]->getID() == id) {
			return i + 10;
		}

	}
	return s + 20;
}

Entity& InventoryComponent::addEntity(int n, std::string id) {
	
	auto& item(manager.addEntity());

	item.setID(id);
	items[n] = &item;
	item.addComponent<itemComponent>(1, n);
	item.addComponent<TransformComponent>((float)80 + n * 48.0f, 600, 32, 32, 1);
	item.addComponent<SpriteComponent>(id);
	item.addComponent<DialogtextComponent>();
	std::stringstream num;
	num << item.getComponent<itemComponent>().getAmount();
	item.getComponent<DialogtextComponent>().setTex(num.str().c_str());
	item.getComponent<DialogtextComponent>().setRender(true);
	return item;
}

void InventoryComponent::addItem(std::string id) {
	int n = findFirstEmptySlot(id);
	std::cout << "2" << std::endl;
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