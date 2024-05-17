#include "Components.h"
#include <iostream>


class InventoryComponent : public Component {
private:
	Manager ItemManager;
	bool slots[10];
	std::string* itemsID[10];
	Entity* items[10];
	int Selected;

	int findFirstEmptySlot() {
		for (int i = 0; i < 10; i++) {
			if (slots[i] != true)
				return i;
		}
		return 11;
	}

	Entity& addEntity(int n, std::string id) {
		auto& item(ItemManager.addEntity());
		slots[n] = true;
		itemsID[n] = &id;
		items[n] = &item;
		item.addComponent<TransformComponent>((float)80 + n * 48.0f, 600, 32, 32, 1);
		item.addComponent<SpriteComponent>(id);
		item.addComponent<FoodComponent>(20);

		return item;
	}
public:

	InventoryComponent() {}
	~InventoryComponent() {}

	void init() {
		Selected = 0;
	};
	void addItem(std::string id) {
		int n = findFirstEmptySlot();
		if (n != 11) {
			// should throw old one 
			// havent made that possible yet
			addEntity(n, id);
		}
		else {
			// should throw old one 
			// havent made that possible yet
			addEntity(Selected, id);
		}
	}

	void update() {
		ItemManager.update();
	}

	void draw() {
		ItemManager.draw();
	}

};