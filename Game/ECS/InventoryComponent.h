#pragma once

#include "Components.h"
#include <iostream>
#include <sstream>

class itemComponent : public Component {
private:
	int amount;
	int slotID;
public:
	itemComponent(int Amount, int SlotID) {
		amount = Amount;
		slotID = SlotID;
	}
	~itemComponent(){}

	int getAmount() { return amount; }
	int getSlotID() { return slotID; }

	void addAmount(int i) { amount += i; }
	void setSlotID(int i) { slotID = i; }

};

class InventoryComponent : public Component {
private:
	Manager ItemManager;
	Entity* items[10];
	int Selected;


	int findFirstEmptySlot(std::string id) {
		int s = NULL;
		for (int i = 0; i < 10; i++) {
			if (items[i]->getComponent<itemComponent>().getAmount() == 0 and s != NULL) {
				s = i;
			}
			
			if (items[i]->getID() == id) {
				return i+10;
			}
			
		}
		return s+20;
	}

	Entity& addEntity(int n, std::string id) {
		auto& item(ItemManager.addEntity());
		
		item.setID(id);
		std::cout << "2" << std::endl;
		items[n] = &item;
		std::cout << "3" << std::endl;
		item.addComponent<itemComponent>(1, n);
		std::cout << "4" << std::endl;
		item.addComponent<TransformComponent>((float)80 + n * 48.0f, 600, 32, 32, 1);
		std::cout << "5" << std::endl;
		item.addComponent<SpriteComponent>(id);
		item.addComponent<DialogtextComponent>();
		std::stringstream num;
		num << item.getComponent<itemComponent>().getAmount();
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
			items[n-10]->getComponent<itemComponent>().addAmount(1);
			std::stringstream num;
			num << items[n-10]->getComponent<itemComponent>().getAmount();
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