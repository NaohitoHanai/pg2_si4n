#include "ObjectManager.h"

void ObjectManager::Init()
{
	objects.clear();
}

void ObjectManager::Update()
{
	// �C�e���[�^�[��
	std::list<GameObject*> eraseObj;

	for (auto itr = objects.begin(); itr != objects.end(); itr++) {
		(*itr)->Update();
		if ((*itr)->IsDestroy()) {
			// ��ŏ���
			eraseObj.push_back(*itr);
		}
	}
	for (GameObject* obj : eraseObj)
	{
		Pop(obj);
		delete obj;
	}
}

void ObjectManager::Draw()
{
	// �͈�for
	for (GameObject* obj : objects) {
		obj->Draw();
	}
}

void ObjectManager::Release()
{
}

void ObjectManager::Push(GameObject* obj)
{
	objects.push_back(obj);
}

void ObjectManager::Pop(GameObject* obj)
{
	for (auto itr = objects.begin(); itr != objects.end();) {
		if (*itr == obj) {
			// ����
			itr = objects.erase(itr);
		}
		else {
			itr++;
		}
	}
}

ObjectManager::ObjectManager()
{
}
