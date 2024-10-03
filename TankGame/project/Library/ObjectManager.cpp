#include "ObjectManager.h"
#include "GameObject.h"
#include <algorithm>
#include <assert.h>

namespace
{
	std::list<GameObject*>* objects;
	bool needSortDraw;
	GameObject* running;
};

void ObjectManager::Init()
{
	objects = new std::list<GameObject*>;
	objects->clear();
	needSortDraw = false;
	running = nullptr;
}

void ObjectManager::Update()
{
	std::list<GameObject*> destroyedObject;
	for (GameObject* obj : *objects)
	{
		running = obj;
		obj->Update();
		running = nullptr;
		if (obj->DestroyRequested())
		{
			destroyedObject.push_back(obj);
		}
	}
	for (GameObject* obj : destroyedObject)
	{
		delete obj;
	}
}

void ObjectManager::Draw()
{
	if (needSortDraw)
	{
		objects->sort([](GameObject* a, GameObject* b) {return a->GetDrawOrder() > b->GetDrawOrder(); });
		needSortDraw = false;
	}
	for (GameObject* node : *objects)
	{
		running = node;
		node->Draw();
		running = nullptr;
	}
}

void ObjectManager::Release()
{
	DeleteAllGameObject();
	objects->clear();
	delete objects;
	objects = nullptr;
}

void ObjectManager::Push(GameObject* obj)
{
	objects->push_back(obj);
	needSortDraw = true;
}

void ObjectManager::SortByDrawOrder()
{
	needSortDraw = true;
}

void ObjectManager::Delete(GameObject* obj)
{
	obj->DestroyMe();
}

void ObjectManager::DeleteAllGameObject()
{
	assert(running == nullptr);

	while (objects->size() > 0) {
		auto itr = objects->begin();
		delete *itr;
		objects->erase(itr);
	}
}

const std::list<GameObject*>& ObjectManager::GetAllObject()
{
	return *objects;
}
