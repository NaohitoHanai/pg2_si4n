#include "GameObject.h"
#include "ObjectManager.h"

GameObject::GameObject()
{
	ObjectManager::GetInst()->Push(this);
	destroy = false;
}

void GameObject::DestroyMe()
{
	destroy = true;
}
