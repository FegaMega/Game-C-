#include "Components.h"
#include <iostream>
#include <sstream>

class InventoryComponent : public Component {
private:
	Manager ItemManager;
	int slots[10];
	std::string itemsID[10];
	Entity* items[10];
	int Selected;


	int findFirstEmptySlot(std::string id) {
		int s = NULL;
		for (int i = 0; i < 10; i++) {
			if (slots[i] == 0 and s != NULL) {
				s = i;
			}
			
			if (itemsID[i] == id) {
				return i+10;
			}
			
		}
		return s+20;
	}

	Entity& addEntity(int n, std::string id) {
		auto& item(ItemManager.addEntity());
		slots[n]++;
		itemsID[n] = id;
		items[n] = &item;
		item.addComponent<TransformComponent>((float)80 + n * 48.0f, 600, 32, 32, 1);
		item.addComponent<SpriteComponent>(id);
		if (id == "Banana") {
			item.addComponent<FoodComponent>(20);
		}
		item.addComponent<DialogtextComponent>();
		std::stringstream num;
		num << slots[n];
		item.getComponent<DialogtextComponent>().setTex(num.str().c_str());
		item.getComponent<DialogtextComponent>().setRender(true);
		return item;
	}
public:

	InventoryComponent() {}
	~InventoryComponent() {}

	void init() {
		Selected = 0;
	};
	void addItem(std::string id) {
		int n = findFirstEmptySlot(id);
		if (n < 10) {
			// should throw old one 
			// havent made that possible yet
			addEntity(n, id);
			
		}
		else if(n < 20) {
			// should throw old one 
			// havent made that possible yet
			slots[n-10]++;
			std::stringstream num;
			num << slots[n-10];
			items[n-10]->getComponent<DialogtextComponent>().setTex(num.str());
		}
		else {
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