#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;
template <typename T> int findinvector(std::vector<T> components, T c) {
	int i = 0;
	for(auto& p : components) {
		if (p == c) {
			return i;
		}
		i++;
	}
}
inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponenets = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitset = std::bitset<maxComponenets>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponenets>;

class Component {
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

};

class Entity {

private:

	Manager& manager;
	bool active = true;
	std::string ID = "none";

	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray{};
	ComponentBitset componentBitset{};
	GroupBitset groupBitset{};

public:

	Entity(Manager& mManager) : manager(mManager) {}

	void update() {
		for (auto& c : components)
		{
			c->entity = this;
			c->update();
	
		}
	}
	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() { return active; }
	void destroy() { active = false; }

	void setID(std::string s) { ID = s; }
	std::string getID() { return ID; }

	bool hasGroup(Group mGroup) {
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	void addGroup(Group mGroup, int i);

	void delGroup(Group mGroup);

	void resetGroup();

	template <typename T> bool hasComponent() const {
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	template<typename T> int delComponent() {
		int i = 0;
		auto y = componentArray[getComponentTypeID<T>()];
		
		
		for (auto& x : components)
		{

			std::cout << x << std::endl;
			std::cout << y << std::endl;
			if (y == x.get()) {
				components.erase(components.begin() + i);
				std::cout << 2 << std::endl;
				break;
			}
			i += 1;
		}
		
		componentArray[getComponentTypeID<T>()] = nullptr;
		componentBitset[getComponentTypeID<T>()] = 0;
		return 0;
	}

	int resetComponent() {
		components.clear();
		componentArray = {};
		componentBitset = {};
		return 0;
	}



};

class Manager {
public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}
	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	void AddToGroup(Entity* mEntity, Group mGroup, int i)
	{
		groupedEntities[mGroup].insert(std::begin(groupedEntities[mGroup]) + i, mEntity);
	}

	void DelFromGroup(Entity* mEntity, Group mGroup)
	{
		int i = findinvector(groupedEntities[mGroup], mEntity);
		groupedEntities[mGroup].erase(std::begin(groupedEntities[mGroup]) + i);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

};