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
	for (auto itr = objects->begin(); itr != objects->end(); )
	{
		GameObject* obj = *itr;
		running = obj;
		obj->Update();
		running = nullptr;
		if (obj->DestroyRequested())
		{
			delete obj;
			itr = objects->erase(itr);
		}
		else
		{
			itr++;
		}
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
	assert(running != obj);
	objects->remove(obj);

	for (auto itr = objects->begin(); itr != objects->end(); )
	{
		if (*itr == obj)
		{
			itr = objects->erase(itr);
		}
		else
			itr++;
	}
}

void ObjectManager::DeleteAllGameObject()
{
	assert(running == nullptr);

	while (objects->size() > 0) {
		delete *(objects->begin());
	}
}

const std::list<GameObject*>& ObjectManager::GetAllObject()
{
	return *objects;
}
