#pragma once

#include "Components.h"
#include <iostream>
#include <sstream>

class itemComponent : public Component {
private:
	int amount = 0;
	int slotID;
	DialogtextComponent* Dialogtext;
public:
	itemComponent(int Amount, int SlotID) {
		amount = Amount;
		slotID = SlotID;
	}
	~itemComponent(){}
	void init() {
		Dialogtext = &entity->getComponent<DialogtextComponent>();
	}

	int getAmount() { return amount; }
	int getSlotID() { return slotID; }

	void addAmount(int i);
	void subAmount(int i);
	void setSlotID(int i) { slotID = i; }

};

class InventoryComponent : public Component {
private:
	Manager manager;
	std::vector<Entity*> items;
	int Selected = 0;
	enum groupLabels : std::size_t {
		inventory
	};

	int findFirstEmptySlot(std::string id);

	Entity& addEntity(int n, std::string id);
	Entity& addEntity(int n, Entity* e);
public:

	InventoryComponent() {}
	~InventoryComponent() {}

	void init() {
		Selected = 0;
		for (int i = 0; i < 10; i++) {
			auto& n(manager.addEntity());
			n.addComponent<itemComponent>(0, i);

			n.addGroup(inventory);
		}
		items = (manager.getGroup(inventory));
	};
	void addItem(std::string id);
	void addItem(Entity* e);
	void destroyItem(Entity* selected);
	void setSelected(int i) { Selected = i; }
	int getSelected() { return Selected; }
	Entity* returnItem();

	void update() {
		manager.refresh();
		manager.update();
	}

	void draw() {
		manager.draw();
	}

};