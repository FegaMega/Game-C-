#include "ECS/ECS.h"

void Entity::addGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}

void Entity::addGroup(Group mGroup, int i)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup, i);
}

void Entity::delGroup(Group mGroup) {
	groupBitset[mGroup] = false;
	manager.DelFromGroup(this, mGroup);
}
void Entity::resetGroup()
{
	groupBitset = {};
	for (int i=0; i < maxGroups; i++)
	{
		if (hasGroup(i) == true)
		{
			manager.DelFromGroup(this, i);
		}
	}
}